package com.fazeilluminati.CanSat;

import java.awt.EventQueue;
import javax.swing.JFrame;
import net.miginfocom.swing.MigLayout;
import javax.swing.JLabel;
import javax.swing.Timer;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.awt.event.ActionEvent;

public class Window {

	private JFrame frmEkcSpitfiresCansat;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Window window = new Window();
					window.frmEkcSpitfiresCansat.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public Window() {
		initialize(); // Run the initialize method
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frmEkcSpitfiresCansat = new JFrame();
		frmEkcSpitfiresCansat.setTitle("EKC Spitfires CanSat 2016-2017"); // Set the window title
		frmEkcSpitfiresCansat.setSize(1280, 720); // Set the window size to 720p, fits nicely on 1080p screens, and fits (although takes up most of the space) on laptop resolutions
		frmEkcSpitfiresCansat.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // Tell the application to exit when closed, instead of hiding
		frmEkcSpitfiresCansat.getContentPane().setLayout(new MigLayout("", "[][][]", "[][][]")); // We're using MigLayout because so far, it doesn't suck
		
		try { // Apply the operating systems theme, instead of using that ugly default one
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
			} 
		catch (ClassNotFoundException | InstantiationException | IllegalAccessException | UnsupportedLookAndFeelException ex) {
		}
		
		JLabel lblComPort = new JLabel("Com Port: ");
		frmEkcSpitfiresCansat.getContentPane().add(lblComPort, "cell 0 0"); // Add com port label
		
		JButton btnConnect = new JButton("Connect");
		btnConnect.addActionListener(new ActionListener() { // Add a listener for the connect button
			public void actionPerformed(ActionEvent arg0) {
				System.out.println("Connected to COM Port: " + Serial.GetPortName()); // Print to console for debug purposes
				lblComPort.setText("Com Port: " + Serial.GetPortName()); // Call a function that will return the port name, so the label will appear as "Com Port: COM13"
				Serial.Connect(); // Run the connect function inside of the Serial class
			}
		});
		frmEkcSpitfiresCansat.getContentPane().add(btnConnect, "cell 1 0,alignx trailing"); // Add the connect button
		
		JButton btnDisconnect = new JButton("Disconnect");
		btnDisconnect.addActionListener(new ActionListener() { // Add a listener for the disconnect button
			public void actionPerformed(ActionEvent e) {
				System.out.println("Disconnected from COM Port: " + Serial.comPort.getSystemPortName()); // Print to console for debug purposes
				lblComPort.setText("Com Port: "); // Remove the system Com Port name when disconnected
				Serial.Disconnect(); // Run the disconnect function inside of the Serial class
			}
		});
		
		frmEkcSpitfiresCansat.getContentPane().add(btnDisconnect, "cell 2 0"); // Add the disconnect button
		
		JLabel lblSystemTime = new JLabel("System time:");
		frmEkcSpitfiresCansat.getContentPane().add(lblSystemTime, "cell 0 1"); // Add the system time title label
		
		JLabel lblTime = new JLabel("time");
		frmEkcSpitfiresCansat.getContentPane().add(lblTime, "cell 1 1"); // Add the time label (we'll modify this later)
		
		JLabel lblSystemDate = new JLabel("System date:");
		frmEkcSpitfiresCansat.getContentPane().add(lblSystemDate, "cell 0 2"); // Add the system date title label
		
		JLabel lblDate = new JLabel("date");
		frmEkcSpitfiresCansat.getContentPane().add(lblDate, "cell 1 2"); // Add the date label (we'll modify this later)
		
		
		final DateFormat timeFormat = new SimpleDateFormat("HH:mm:ss"); // Declare the time format we want to use
		final DateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy"); // Declare the date format we want to use
        ActionListener timerListener = new ActionListener() // Create a listener
        {
            public void actionPerformed(ActionEvent e)
            {
                Date date = new Date();
                String time = timeFormat.format(date);
                String theDate = dateFormat.format(date);
                lblTime.setText(time); // Set the time
                lblDate.setText(theDate); // Set the date
                // Trying to integrate the connect and disconnect functions into one button, experimental atm
                /*
                if (Serial.comPort.isOpen()) {
					btnConnect.setText("Disconnect");
				}
                if (!Serial.comPort.isOpen()) {
					btnConnect.setText("Connect");
				}
				*/
            }
        };
        Timer timer = new Timer(1000, timerListener); // Every second, loop the code above
        timer.setInitialDelay(0); // to make sure it doesn't wait one second at the start
        timer.start();
	}
}