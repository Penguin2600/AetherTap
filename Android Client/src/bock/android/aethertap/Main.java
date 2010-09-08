package bock.android.aethertap;

import java.net.InetAddress;
import android.app.Activity;
import android.app.ProgressDialog;
import android.os.AsyncTask;
import android.os.Bundle;
import android.content.res.Configuration;
import android.view.KeyEvent;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class Main extends Activity {
	TextView textDebug = null;
	udpHandler Udp = new udpHandler(this);
	String knownIP = null;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		Layout();
	}

	public void onConfigurationChanged(Configuration newConfig) {
		super.onConfigurationChanged(newConfig);
		Layout();
	}

	private void Layout() {
		setContentView(R.layout.main);
		Button buttonListen = (Button) findViewById(R.id.buttonListen);
		Button buttonProbe = (Button) findViewById(R.id.buttonProbe);
		Button buttonTelnet = (Button) findViewById(R.id.buttonTelnet);
		textDebug = (TextView) findViewById(R.id.textDebug);

		buttonListen.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				new DeviceListenerTask().execute();
			}
		});
		buttonProbe.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				new DeviceProbeTask().execute();
			}
		});
		buttonTelnet.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {

			}
		});
	}

	private class DeviceListenerTask extends
			AsyncTask<InetAddress, Integer, InetAddress> {
		ProgressDialog dialog = null;

		@Override
		protected void onPreExecute() {
			dialog = ProgressDialog.show(Main.this, "",
					"Listening for Device....", true);
		}

		@Override
		protected InetAddress doInBackground(InetAddress... params) {
			return Udp.listenForDevice();
		}

		protected void onPostExecute(InetAddress result) {
			knownIP=result.toString().split("/")[1];
			createSocket();
			dialog.dismiss();
		}
	}

	private class DeviceProbeTask extends
			AsyncTask<InetAddress, Integer, InetAddress> {
		ProgressDialog dialog = null;

		@Override
		protected void onPreExecute() {
			dialog = ProgressDialog.show(Main.this, "",
					"Probing for Device....", true);
		}

		@Override
		protected InetAddress doInBackground(InetAddress... params) {
			return Udp.probeForDevice();
		}

		protected void onPostExecute(InetAddress result) {
			knownIP=result.toString().split("/")[1];
			createSocket();
			dialog.dismiss();
		}

	}
	
	private void createSocket() {
		if (Udp.comSocket==null)
		{
			Udp.openCom();
			textDebug.setText("Active Device Found At "+knownIP);
		} else {
			textDebug.setText("Ip Change To "+knownIP);
		}
	}
	
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		if (Udp.comSocket!=null) {
			switch (keyCode) {
			case KeyEvent.KEYCODE_DPAD_DOWN:
				Udp.sendArray("s",knownIP);
				return true;
			case KeyEvent.KEYCODE_DPAD_LEFT:
				Udp.sendArray("a",knownIP);
				return true;
			case KeyEvent.KEYCODE_DPAD_RIGHT:
				Udp.sendArray("d",knownIP);
				return true;
			case KeyEvent.KEYCODE_DPAD_UP:
				Udp.sendArray("w",knownIP);
				return true;
			}
		}

		return super.onKeyDown(keyCode, event);
	}

	protected void onStart() {
		super.onStart();
	}

	protected void onRestart() {
		super.onRestart();
	}

	protected void onResume() {
		super.onResume();
	}

	protected void onPause() {
		super.onPause();
	}

	protected void onStop() {
		super.onStop();
	}

	protected void onDestroy() {
		super.onDestroy();
	}

}