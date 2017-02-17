package com.fazeilluminati.CanSat;

import java.io.IOException;
import java.io.InputStream;

import com.fazecast.jSerialComm.SerialPort;

public class Serial {
	
	public static SerialPort comPort = SerialPort.getCommPorts()[0];;
	
	public static void Connect() {
		comPort.openPort();
		comPort.setComPortTimeouts(SerialPort.TIMEOUT_READ_SEMI_BLOCKING, 100, 0);
		InputStream in = comPort.getInputStream();
		new Thread() {
		        @Override
		        public void run() {
		    		try
		    		{
		    		   while (comPort.isOpen())
		    		      System.out.print((char)in.read());
		    		   in.close();
		    		} catch (Exception e) { e.printStackTrace(); }
		    		comPort.closePort();
		            }
		    }.start();
		}
	
	public static void Disconnect() {
		InputStream in = comPort.getInputStream();
		try {
			in.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		comPort.closePort();
	}
	
	public static String GetPortName() {
		return comPort.getSystemPortName();
	}
}