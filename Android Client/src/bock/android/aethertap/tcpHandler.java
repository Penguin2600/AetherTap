package bock.android.aethertap;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;

public class tcpHandler {
	Socket tSocket = null;
	
	private static final int TELNET_PORT = 23;
	
	public tcpHandler(String address) {
		
		try {
			tSocket = new Socket(address, TELNET_PORT);
		} catch (UnknownHostException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public void doTelnet(String key) {
		try {
			PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(tSocket.getOutputStream())), true);
			out.println(key);
		} catch (UnknownHostException e) {

			e.printStackTrace();
		} catch (IOException e) {

			e.printStackTrace();
		}
	}
	
	public void destroy(){
		try {
			tSocket.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
