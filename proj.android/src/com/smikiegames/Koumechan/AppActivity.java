/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.smikiegames.Koumechan;

import android.app.Activity;
import android.content.Intent;
import android.content.IntentSender;
import android.os.Bundle;
import android.util.Log;
import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.Scopes;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.plus.PlusClient;
import com.google.android.gms.plus.model.people.Person;
import org.cocos2dx.lib.Cocos2dxActivity;

import com.google.android.gms.common.GooglePlayServicesClient.ConnectionCallbacks;

public class AppActivity extends Cocos2dxActivity implements ConnectionCallbacks,GoogleApiClient.OnConnectionFailedListener {
	private static AppActivity me = null;
    private static final String TAG = "AppActivity";
    private PlusClient mPlusClient  = null;
    private ConnectionResult mConnectionResult = null;
    private static final int REQUEST_CODE_RESOLVE_ERR = 9000;
    private static final int REQUEST_TRYSILENT = 0;
    private static final int REQUEST_SIGN_IN = 1;

	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
        Log.d(TAG,"onCreate");
        me = this;

	}
    public void createPlusClient()
    {
        if(mPlusClient == null){
            mPlusClient = new PlusClient.Builder(this,this,this)
                    .setScopes(Scopes.PLUS_LOGIN)
                    .build();
            Log.d(TAG,"create PlusClient");
        }
    }

	public static native boolean onResult(int stat,String gppid,String gmail,String gurl,String gName);

	public static void gppSignIn(){
        Log.d(TAG,"gppSignIn");
        if(me != null){
            if(me.mPlusClient == null){
                me.createPlusClient();
            }
            try{
                if(me.mConnectionResult != null){
                    me.mConnectionResult.startResolutionForResult(me,REQUEST_SIGN_IN);
                }
                else{
                    Log.d(TAG,"gppsignin connectionResult is null");
                    me.mPlusClient.connect();
                }
            }
            catch(IntentSender.SendIntentException e){
                Log.d(TAG,"IntentSenderException " + e.getMessage());
                me.mConnectionResult = null;
                me.mPlusClient.connect();
            }
        }
	}
	public static void gppSignOut(){
        if(me != null && me.mPlusClient != null){
            if(me.mPlusClient.isConnected()){
                Log.d(TAG,"gppSignOut");
                me.mPlusClient.clearDefaultAccount();;
                me.mPlusClient.disconnect();
                onResult(-1,null,null,null,null);
            }
        }
	}
	public static boolean isSignIn(){
        if(me != null && me.mPlusClient != null){
            if(me.mPlusClient.isConnected()){
                Log.d(TAG,"isSignIn connected");
            }
            Log.d(TAG, "isSignIn");
            return me.mPlusClient.isConnected();
        }
        return false;
	}
    public static boolean trySilentSignIn(){
        Log.d(TAG,"trySilentSignIn");
        if(me.mPlusClient == null){
            me.createPlusClient();
        }
        if(me.mPlusClient != null){
            try{
                if(!me.mPlusClient.isConnected() && !me.mPlusClient.isConnecting()){
                    if(me.mConnectionResult != null){
                        me.mConnectionResult.startResolutionForResult(me,REQUEST_TRYSILENT);
                        return true;
                    }
                }
                else{
                    Log.d(TAG,"try silent but already connected");
                }
            }
            catch(IntentSender.SendIntentException e){
                Log.d(TAG,"try " + e.getMessage());
            }
            me.mConnectionResult = null;
            me.mPlusClient.connect();
        }
        else{
            Log.d(TAG,"try plusclient is null");
        }
        return false;
    }


    @Override
    protected void onStart() {
        Log.d(TAG,"onStart");
        super.onStart();
        if(mPlusClient != null){
            mPlusClient.connect();
            Log.d(TAG,"re connect");
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        Log.d(TAG,"activity result " + requestCode + " result " + resultCode);
        if(requestCode == REQUEST_SIGN_IN || requestCode == REQUEST_TRYSILENT  || requestCode == REQUEST_CODE_RESOLVE_ERR){
            if(mPlusClient != null){
                if( resultCode == RESULT_OK && !mPlusClient.isConnected() && !mPlusClient.isConnecting()){
                    mConnectionResult = null;
                    mPlusClient.connect();
                }
            }
            else{
                Log.d(TAG,"onActivityResult PlusClient is null");
            }
        }
    }

    @Override
    protected void onStop() {
        Log.d(TAG,"OnStop");
        super.onStop();
        if(mPlusClient != null){
            mPlusClient.disconnect();
        }
    }

    @Override
    public void onConnected(Bundle bundle) {
        if(mPlusClient != null){
            String accountName = mPlusClient.getAccountName();
            Log.d(TAG,"onConnected " + accountName);
            Person person = mPlusClient.getCurrentPerson();
            if(person != null){
                Log.d(TAG,"person info " + person.getId() + " " + person.getDisplayName());
                onResult(1,person.getId(),accountName,person.getImage().getUrl(),person.getDisplayName());
            }
            else{
                Log.d(TAG,"connected but person is null");
            }
        }
        else{
            Log.d(TAG," onConnected PlusConnect is null");
        }
    }

    @Override
    public void onDisconnected() {
        Log.d(TAG,"disconnect");
        onResult(-1,null,null,null,null);
    }

    @Override
    public void onConnectionFailed(ConnectionResult connectionResult) {
        if(connectionResult != null && connectionResult.hasResolution()){
            try{
                Log.d(TAG,"connection failed");
                connectionResult.startResolutionForResult(this,REQUEST_CODE_RESOLVE_ERR);
            }
            catch(IntentSender.SendIntentException e){
                if(mPlusClient != null){
                    mPlusClient.connect();
                }
                else{
                    Log.d(TAG,"in connectFailed plusClient is null");
                }
            }
            mConnectionResult = connectionResult;
        }
    }
}
