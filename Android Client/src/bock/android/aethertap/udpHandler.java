package bock.android.aethertap;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

import android.content.Context;
import android.net.DhcpInfo;
import android.net.wifi.WifiManager;

public class udpHandler {

	private static final int DISCOVERY_PORT = 30303;
	private static final int COM_PORT = 2222;

	InetAddress nAddr = null;
	DatagramSocket comSocket = null;
	Context context = null;

	public udpHandler(Context c) {
		context = c;
	}

	protected InetAddress getBroadcastAddress() throws IOException {
		WifiManager wifi = (WifiManager) context
				.getSystemService(Context.WIFI_SERVICE);
		DhcpInfo dhcp = wifi.getDhcpInfo();
		// handle null somehow
		int broadcast = (dhcp.ipAddress & dhcp.netmask) | ~dhcp.netmask;
		byte[] quads = new byte[4];
		for (int k = 0; k < 4; k++)
			quads[k] = (byte) ((broadcast >> k * 8) & 0xFF);
		return InetAddress.getByAddress(quads);
	}

	protected InetAddress listenForDevice() {
		try {
			nAddr = InetAddress.getLocalHost();
			byte[] buf = new byte[1024];
			DatagramSocket socket = new DatagramSocket(DISCOVERY_PORT);
			socket.setSoTimeout(5000);
			DatagramPacket packet = new DatagramPacket(buf, buf.length);
			socket.receive(packet);
			socket.close();
			return packet.getAddress();
		} catch (Exception e) {
			return nAddr;
		}
	}

	protected InetAddress probeForDevice() {
		try {
			DatagramSocket socket = new DatagramSocket(DISCOVERY_PORT);
			socket.setBroadcast(true);
			String data = String.format("Discovery: Anyone out there?");
			DatagramPacket packet = new DatagramPacket(data.getBytes(), data
					.length(), getBroadcastAddress(), DISCOVERY_PORT);
			socket.send(packet);
			socket.close();
			return listenForDevice();
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		}
	}

	protected void openCom() {
		try {
			comSocket = new DatagramSocket(COM_PORT);
		} catch (SocketException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	protected void closeCom() {
		comSocket.close();
	}

	protected void sendArray(String data, String dst) {
		try {
			InetAddress Destination = InetAddress.getByName(dst);
			comSocket.setBroadcast(false);
			DatagramPacket packet = new DatagramPacket(data.getBytes(), data
					.length(), Destination, COM_PORT);
			comSocket.send(packet);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
