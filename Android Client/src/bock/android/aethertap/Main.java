package bock.android.aethertap;

import java.io.IOException;
import java.net.InetAddress;
import java.text.DecimalFormat;

import android.app.Activity;
import android.app.ProgressDialog;
import android.os.AsyncTask;
import android.os.Bundle;
import android.content.Context;
import android.content.res.Configuration;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorManager;
import android.hardware.SensorEventListener;

public class Main extends Activity {

	TextView textDebug = null;
	TextView textAccelx = null;
	TextView textAccely = null;
	TextView textAccelz = null;
	TextView textMyIP = null;
	TextView textNetmask = null;
	TextView textRemoteIP = null;
	InetAddress knownIPaddr = null;
	udpHandler Udp = new udpHandler(this);
	String knownIP = null;
	short[] accelvals= new short[3];
	
	private SensorManager sensorMgr;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		
		sensorMgr = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
		sensorMgr.registerListener(accListener, sensorMgr
				.getDefaultSensor(Sensor.TYPE_ACCELEROMETER),
				SensorManager.SENSOR_DELAY_NORMAL);
		
		Layout();
	}

	@Override
	public void onConfigurationChanged(Configuration newConfig) {
		super.onConfigurationChanged(newConfig);
		Layout();
	}

	private void Layout() {
		setContentView(R.layout.main);
		Button buttonListen = (Button) findViewById(R.id.buttonListen);
		Button buttonProbe = (Button) findViewById(R.id.buttonProbe);
		Button buttonP1 = (Button) findViewById(R.id.buttonP1);
		Button buttonP2 = (Button) findViewById(R.id.buttonP2);
		Button buttonP3 = (Button) findViewById(R.id.buttonP3);
		Button buttonP4 = (Button) findViewById(R.id.buttonP4);
		textDebug = (TextView) findViewById(R.id.textDebug);
		textAccelx = (TextView) findViewById(R.id.textAccelx);
		textAccely = (TextView) findViewById(R.id.textAccely);
		textAccelz = (TextView) findViewById(R.id.textAccelz);
		textNetmask = (TextView) findViewById(R.id.textNetmask);
		textRemoteIP = (TextView) findViewById(R.id.textRemoteIP);
		
		try {
			textNetmask.setText(Udp.getBroadcastAddress().toString().split("/")[1]);
		} catch (IOException e) {
			e.printStackTrace();
		}
		textRemoteIP.setText("127.0.0.1");

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
		buttonP1.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				
				char Xh = (char)(accelvals[0] & 0xff);
				char Xl = (char)((accelvals[0] >> 8) & 0xff);
				char Yh = (char)(accelvals[1] & 0xff);
			    char Yl = (char)((accelvals[1] >> 8) & 0xff);

				Udp.sendArray("r"+Xh+Xl+Yh+Yl, knownIP);
			}
		});
		buttonP2.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				Udp.sendArray("2", knownIP);
			}
		});
		buttonP3.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				Udp.sendArray("3", knownIP);
			}
		});
		buttonP4.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				Udp.sendArray("4", knownIP);
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

		@Override
		protected void onPostExecute(InetAddress result) {
			knownIP = result.toString().split("/")[1];
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

		@Override
		protected void onPostExecute(InetAddress result) {
			knownIP = result.toString().split("/")[1];
			createSocket();
			dialog.dismiss();
		}

	}

	private void createSocket() {
		if (Udp.comSocket == null) {
			Udp.openCom();
			textRemoteIP.setText(knownIP);
		} else {
			textRemoteIP.setText(knownIP);
		}
	}

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		if (Udp.comSocket != null) {
			switch (keyCode) {
			case KeyEvent.KEYCODE_DPAD_UP:
				Udp.sendArray("1", knownIP);
				return true;
			}
		}
		return super.onKeyDown(keyCode, event);
	}

	private final SensorEventListener accListener = new SensorEventListener() {
		@Override
		public void onAccuracyChanged(Sensor sensor, int accuracy) {
		}
		@Override
		public void onSensorChanged(SensorEvent event) {
			
			DecimalFormat df = new DecimalFormat("0");
			
			for (int i=0; i<=2; i++){
					accelvals[i] = (short) (((event.values[i]/(float)10)*2000)+2000);
			}
			
			String x_v = df.format(accelvals[0]);
			String y_v = df.format(accelvals[1]);
			String z_v = df.format(accelvals[2]);
			
			textAccelx.setText("X Axis: "+x_v);
			textAccely.setText("Y Axis: "+y_v);
			textAccelz.setText("Z Axis: "+z_v);

		}
	};


	@Override
	protected void onStart() {
		super.onStart();
	}

	@Override
	protected void onRestart() {
		super.onRestart();
	}

	@Override
	protected void onResume() {
		super.onResume();
	}

	@Override
	protected void onPause() {
		super.onPause();
	}

	@Override
	protected void onStop() {
		super.onStop();
		sensorMgr.unregisterListener(accListener);
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		sensorMgr.unregisterListener(accListener);

	}

}