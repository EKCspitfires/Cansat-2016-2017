package com.fazeilluminati.CanSat;
import java.io.InputStream;
import java.text.SimpleDateFormat;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.Date;
import org.eclipse.swt.SWT;
import org.eclipse.swt.graphics.Image;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Combo;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.Shell;
import com.fazecast.jSerialComm.SerialPort;
public class Main {
	
	public static void main(String[] args) {
		EKCSpitfires();	
	}
	
	
	// I'll probably separate all of this code into their own class files one day :)
	
	static void EKCSpitfires() {
		
		// Defining the window
		Display display = new Display();
		Shell shell = new Shell(display);
		shell.setSize(1280, 720); // Set the window size
		shell.setText("CanSat EKC Spitfires 2016-2017"); // Set the window title
		InputStream shelliconstream = Main.class.getResourceAsStream("EKC.ico"); // Set the window icon. Apparently you need to do this for relative icons
		Image shellicon = new Image(display, shelliconstream);
		shell.setImage(shellicon);
		
		// Define the grid layout
		GridLayout gridLayout = new GridLayout(4, false);
		gridLayout.verticalSpacing = 8;
		shell.setLayout(gridLayout);
	
		
		
		
		
		// Begin adding outputs to display in the window
		
		
		
		
		// TODO COM Port
		Label comlabel = new Label(shell, SWT.NULL);
		comlabel.setText("COM Port: ");
		final Combo COMcombo = new Combo(shell, SWT.NULL); // By using SWT.NULL (instead of SWT.READ_ONLY), we can type custom COM ports in that aren't in the list. I'm looking at you Jai.
		COMcombo.setBounds(50, 50, 150, 65);
		String comitems[] = { "1", "2", "3", "4", "5" }; // We cab use COMcombo.getText() to grab the value of the selected COM port
		COMcombo.setItems(comitems);
		COMcombo.select(0);
		
		
		// Set grid data
		GridData comgridData = new GridData(GridData.BEGINNING);
		comgridData.widthHint = 20; // Make the combo box longer to allow up to 3 place numbers
		COMcombo.setLayoutData(comgridData);
				
		
		
		// TODO Connect button
		Button combutton = new Button(shell, SWT.PUSH); // We're adding a push-able button that will be used later
		combutton.setText("Connect"); // The button's text will display "Connect"
		
		
		
		
		// TODO Com connection - This code does absolutely nothing right now
		SerialPort comPort = SerialPort.getCommPort((COMcombo.getText())); // Here, we're defining comPort as a serial port, with the value of our combo box, defined earlier in the code
		comPort.openPort();
		comPort.setComPortTimeouts(SerialPort.TIMEOUT_READ_SEMI_BLOCKING, 100, 0);
		InputStream comIn = comPort.getInputStream();
		try {
			for (int j = 0; j < 1000; ++j)
				//System.out.print((char)comIn.read());
			comIn.close();
			} catch (Exception e) {
				e.printStackTrace();
			}
		comPort.closePort();
	
		
		
		
		/* Not sure what I'll do with this bit yet
		Thread comconnection = new Thread() {
			public void run() {
				while (true) {
					try {
						Thread.sleep(1000);
						display.asyncExec(new Runnable() {
							@Override
							public void run() {
									System.out.println("Looping with port: " + COMcombo.getText());
							}
						});
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			}
		};
		// comconnection.start(); // Begin the thread - I'm using a button to begin the thread instead
		*/
		
		// TODO Connect button listener
		combutton.addListener(SWT.Selection, new Listener() { // Here, we add the listener to watch for when the button is pressed
			public void handleEvent(Event e) {
				switch (e.type) {
				case SWT.Selection: // If the button has been selected (pressed), the following actions will take place
					comPort.closePort(); // Close any already open connections
					comPort.openPort(); // Open a new connection
					//comconnection.start(); // This is still buggy and causes the application to crash when pressed twice. 
					System.out.println("Connected to COM port: " + COMcombo.getText()); // Print the connected port in the console for debug purposes
					break;
					}
				}
			});
		
		
		
		// TODO System Time
		Label systemtime = new Label(shell, SWT.NULL);
		systemtime.setText("System time: " + new SimpleDateFormat("HH:mm:ss").format(new Date())); // This is needed to display the time without a 1 second delay 
		// Create a thread called time to run on a loop
		Thread time = new Thread() {
			public void run() {
				while(true) {
					try {
						Thread.sleep(1000);
						display.asyncExec(new Runnable() {
							@Override
							public void run() {
								systemtime.setText("System time: " + new SimpleDateFormat("HH:mm:ss").format(new Date())); // Update the time every second
							}
						});
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			}
		};
		time.start(); // Begin the thread
		
		// Set grid data
		GridData timegridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		timegridData.horizontalSpan = 3;
		systemtime.setLayoutData(timegridData);
		
		
		
		
		// TODO System date
		Label systemdate = new Label(shell, SWT.NULL);
		systemdate.setText("System date: " + DateTimeFormatter.ofPattern("dd/MM/yyyy").format(LocalDate.now())); // This is needed to display the date without a 1 second delay 
		// Create a thread called date to run on a loop
		Thread date = new Thread() {
			public void run() {
				while(true) {
					try {
						Thread.sleep(1000);
						display.asyncExec(new Runnable() {
							@Override
							public void run() {
								systemdate.setText("System date: " + DateTimeFormatter.ofPattern("dd/MM/yyyy").format(LocalDate.now())); // Update the date every second
							}
						});
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			}
		};
		date.start(); // Begin the thread
		
		// Set grid data
		GridData dategridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		dategridData.horizontalSpan = 3;
		systemdate.setLayoutData(dategridData);
		
		
		
		// TODO Can temperature
		Label cantemperature = new Label(shell, SWT.NULL);
		cantemperature.setText("Temperature (°C): " + "Initialising"); // This is needed to display the temperature without a 0.5 second delay 
		// Create a thread called cantemp to run on a loop
		int temp = 30;
		Thread cantemp = new Thread() {
			public void run() {
				while(true) {
					try {
						Thread.sleep(500);
						display.asyncExec(new Runnable() {
							@Override
							public void run() {
								cantemperature.setText("Temperature (°C): " + temp); // Update the received temperature every 0.5 seconds
							}
						});
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			}
		};
		cantemp.start(); // Begin the thread
		
		// Set grid data
		GridData tempgridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		tempgridData.horizontalSpan = 3;
		cantemperature.setLayoutData(tempgridData);
		
		
		
		
		// TODO Can longitude
		Label canlongitude = new Label(shell, SWT.NULL);
		canlongitude.setText("Longitude: " + "Initialising"); // This is needed to display the longitude without a 0.5 second delay 
		// Create a thread called canlong to run on a loop
		int longd = 1337;
		Thread canlong = new Thread() {
			public void run() {
				while(true) {
					try {
						Thread.sleep(500);
						display.asyncExec(new Runnable() {
							@Override
							public void run() {
								canlongitude.setText("Longitude: " + longd); // Update the received longitude every 0.5 seconds
							}
						});
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			}
		};
		canlong.start(); // Begin the thread
		
		// Set grid data
		GridData longgridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		longgridData.horizontalSpan = 3;
		canlongitude.setLayoutData(longgridData);
		
		
		
		
		// TODO Can latitude
		Label canlatitude = new Label(shell, SWT.NULL);
		canlatitude.setText("Latitude: " + "Initialising"); // This is needed to display the latitude without a 0.5 second delay 
		// Create a thread called canlat to run on a loop
		int lat = 999;
		Thread canlat = new Thread() {
			public void run() {
				while(true) {
					try {
						Thread.sleep(500);
						display.asyncExec(new Runnable() {
							@Override
							public void run() {
								canlatitude.setText("Latitude: " + lat); // Update the received latitude every 0.5 seconds
							}
						});
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			}
		};
		canlat.start(); // Begin the thread
		
		// Set grid data
		GridData latgridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		latgridData.horizontalSpan = 3;
		canlatitude.setLayoutData(latgridData);
		
		
		
		
		// TODO Can pressure
		Label canpressure = new Label(shell, SWT.NULL);
		canpressure.setText("Pressure: " + "Initialising"); // This is needed to display the pressure without a 0.5 second delay 
		// Create a thread called canpress to run on a loop
		int press = 21;
		Thread canpress = new Thread() {
			public void run() {
				while(true) {
					try {
						Thread.sleep(500);
						display.asyncExec(new Runnable() {
							@Override
							public void run() {
								canpressure.setText("Pressure: " + press); // Update the received pressure every 0.5 seconds
							}
						});
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			}
		};
		canpress.start(); // Begin the thread
		
		// Set grid data
		GridData pressgridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		pressgridData.horizontalSpan = 3;
		canpressure.setLayoutData(pressgridData);
		
		
		
		// TODO Can acceleration
		Label canacceleration = new Label(shell, SWT.NULL);
		canacceleration.setText("Acceleration: " + "Initialising"); // This is needed to display the pressure without a 0.5 second delay 
		// Create a thread called canaccel to run on a loop
		int accelx = 100;
		int accely = 200;
		int accelz = 300;
		Thread canaccel = new Thread() {
			public void run() {
				while(true) {
					try {
						Thread.sleep(500);
						display.asyncExec(new Runnable() {
							@Override
							public void run() {
								canacceleration.setText("Acceleration: " + "X: " + accelx + " Y: " + accely + " Z: " + accelz); // Update the received pressure every 0.5 seconds
							}
						});
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			}
		};
		canaccel.start(); // Begin the thread
		
		// Set grid data
		GridData accelgridData = new GridData(GridData.FILL_HORIZONTAL);
		accelgridData.horizontalSpan = 3;
		canacceleration.setLayoutData(accelgridData);
		
		
		
		
		// TODO Open the shell
		shell.open();
		while (!shell.isDisposed()) {
			if (!display.readAndDispatch()) display.sleep();
		}
		display.dispose();
	}
}