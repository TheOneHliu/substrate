package com.example.substrate;

import java.io.IOException;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.UnknownHostException;

import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;

public class MainActivity extends ActionBarActivity {
	TestSub ts = new TestSub();
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		ts.hookDemo();
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}
	
	public void OnClick(View v){
		Log.i("OnClick", "OnClick");
		new Thread(run).start();
	}
	
	public Runnable run = new Runnable(){
		@Override
		public void run() {
			try {
				Socket client = new Socket();
				InetAddress address = InetAddress.getByName("www.baidu.com");
				Log.i("InetAddress.getByName", "InetAddress.getByName www.baidu.com: " + address.getHostAddress());
//				long connect_before = SystemClock.uptimeMillis();
				client.connect(new InetSocketAddress(address,
						80));
				client.close();
			} catch (UnknownHostException e) {
//				 TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e) {
//				 TODO Auto-generated catch block
				e.printStackTrace();
			}	
		}
	};
}
