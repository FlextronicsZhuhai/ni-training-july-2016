/**
 *
 * Title      : Computer.java
 * Purpose    : Java class that contains the computer motherboard example functionality.
 *		This example class shows how to pass data to/from Teststand. 
 *
 */

import java.awt.Color;

public class Computer {
    
    // The location of the images folder relative to the TestStand root folder 
    public static final String BITMAP_LOCATION = "\\Examples\\Custom Step Types\\Java Step Types\\images";

    // The name of the computer motherboard image
    public static final String BITMAP_NAME = "compMotherBoard.jpg";

    // These variables store the state of the tests selected to fail from the displayed dialog 
    private static boolean powerOnCheck = false;
    private static boolean videoCheck = false; 
    private static boolean keyboardCheck = false;
    private static boolean CPUCheck = false;
    private static boolean ROMCheck = false;
    private static boolean RAMCheck = false;
    
    // The path of the image displayed by the dialog
    private static String imagePath;

    /** 
     * Purpose    : Creates new Computer form 
     * Parameters : args - The location of the TestStand root folder as the first argument 
     */
    public Computer(String testStandPath) {
	  // Build the complete name and path of the bitmap
	  imagePath = new String(testStandPath);
	  imagePath = imagePath.concat(BITMAP_LOCATION).concat(BITMAP_NAME);

	  // initialize frame and dialog
  	  parent = new javax.swing.JFrame("Demo");
	  dialog = new javax.swing.JDialog(parent,true);       	  
	  dialog.getContentPane().setLayout(null);
	  
	  // initialize components in dialog 
	  initComponents();

	  // resize and show dialog
	  dialog.setModal(true);
	  dialog.setResizable(false);
	  dialog.setSize(510,460);
	  dialog.setLocationRelativeTo(null);
	  dialog.show();
    }

    /** This method is called from within the constructor to initialize the form
     * and all the controls on it.
     */
    private void initComponents() {
        jPanel1 = new javax.swing.JPanel();
        jLabel2 = new javax.swing.JLabel();
        diagram = new javax.swing.JLabel();
        doneButton = new javax.swing.JButton();
        powerOnCheckbox = new javax.swing.JCheckBox();
        videoCheckbox = new javax.swing.JCheckBox();
        keyboardCheckbox = new javax.swing.JCheckBox();
        CPUCheckbox = new javax.swing.JCheckBox();
        ROMCheckbox = new javax.swing.JCheckBox();
        RAMCheckbox = new javax.swing.JCheckBox();
        
        dialog.getContentPane().setLayout(null);
        
        dialog.addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent evt) {
                closeDialog(evt);
            }
        });
        
        jPanel1.setLayout(null);
        
        jLabel2.setText("Check tests which should FAIL:");
        jLabel2.setForeground(java.awt.Color.black);
        jLabel2.setFont(new java.awt.Font("Arial", 0, 18));
        jPanel1.add(jLabel2);
        jLabel2.setBounds(120, 20, 300, 30);
        
        doneButton.setFont(new java.awt.Font("Dialog", 0, 12));
        doneButton.setText("Done");
		doneButton.setBorder(new javax.swing.border.SoftBevelBorder(javax.swing.border.BevelBorder.RAISED));
        doneButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                doneButtonActionPerformed(evt);
            }
        });
        
        jPanel1.add(doneButton);
        doneButton.setBounds(220, 380, 70, 30);
        doneButton.setBackground(Color.WHITE);
        doneButton.setBorder(javax.swing.BorderFactory.createLineBorder(Color.GRAY));
        
        powerOnCheckbox.setFont(new java.awt.Font("Dialog", 0, 12));
        powerOnCheckbox.setText("Power On");        
        jPanel1.add(powerOnCheckbox);
        powerOnCheckbox.setBounds(35, 57, 85, 25);
        powerOnCheckbox.setBackground(Color.WHITE);
        
        videoCheckbox.setFont(new java.awt.Font("Dialog", 0, 12));
        videoCheckbox.setText("Video");     
        jPanel1.add(videoCheckbox);
        videoCheckbox.setBounds(35, 88, 65, 25);
        videoCheckbox.setBackground(Color.WHITE);
        
        keyboardCheckbox.setFont(new java.awt.Font("Dialog", 0, 12));
        keyboardCheckbox.setText("Keyboard");
        jPanel1.add(keyboardCheckbox);
        keyboardCheckbox.setBounds(35, 272, 85, 25);
        keyboardCheckbox.setBackground(Color.WHITE);

        CPUCheckbox.setFont(new java.awt.Font("Dialog", 0, 12));
        CPUCheckbox.setText("CPU");
        jPanel1.add(CPUCheckbox);
        CPUCheckbox.setBounds(35, 150, 52, 25);
        CPUCheckbox.setBackground(Color.WHITE);
        
        ROMCheckbox.setFont(new java.awt.Font("Dialog", 0, 12));
        ROMCheckbox.setText("ROM");
        jPanel1.add(ROMCheckbox);
        ROMCheckbox.setBounds(35, 175, 52, 25);
        ROMCheckbox.setBackground(Color.WHITE);
        
        RAMCheckbox.setFont(new java.awt.Font("Dialog", 0, 12));
        RAMCheckbox.setText("RAM");
        jPanel1.add(RAMCheckbox);
        RAMCheckbox.setBounds(35, 198, 52, 25);
        RAMCheckbox.setBackground(Color.WHITE);
        
        diagram.setIcon(new javax.swing.ImageIcon(imagePath));
        jPanel1.add(diagram);
        diagram.setBounds(110, 60, 370, 310);
        
        dialog.getContentPane().add(jPanel1);
        jPanel1.setBounds(0, 0, 510, 460);
        jPanel1.setBackground(Color.WHITE);
       
	dialog.pack();
    }

    /** Closes the dialog through the Done button */
    private void doneButtonActionPerformed(java.awt.event.ActionEvent evt) {
        saveSettingsAndCloseDialog();
    }

    /** Closes the dialog by any other means */
    private void closeDialog(java.awt.event.WindowEvent evt) {
	  saveSettingsAndCloseDialog();
    }

    /** Save the state of selection on the dialog and cleanup the dialog */
    private void saveSettingsAndCloseDialog() {
  	  // Save values of checkboxes
	  powerOnCheck = powerOnCheckbox.isSelected();
	  videoCheck = videoCheckbox.isSelected();  	  
	  keyboardCheck = keyboardCheckbox.isSelected();        
	  CPUCheck = CPUCheckbox.isSelected();
	  ROMCheck = ROMCheckbox.isSelected();
	  RAMCheck = RAMCheckbox.isSelected();

	  // Close dialog and exit
	  dialog.setVisible(false);
	  parent.dispose();
    }

    // These methods are used to retrieve the tests selected to FAIL.
    public static boolean isPowerOnChecked() {
	return powerOnCheck;
    }    

    public static boolean isVideoChecked() {
	return videoCheck;
    }
    
    public static boolean isKeyboardChecked() {
	return keyboardCheck;
    }

    public static boolean isCPUChecked() {
	return CPUCheck;
    }
    
    public static boolean isROMChecked() {
	return ROMCheck;
    }

    public static boolean isRAMChecked() {
	return RAMCheck;
    }

    // These methods are used to determine if a particular test passed or failed
    public int powerOnTest(boolean passFail) {
		if (passFail == true) 
			return 13;
		else 
			return 10;
    }

    public boolean videoTest(boolean passFail) {
		return !passFail;
    }

    public boolean keyboardTest(boolean passFail) {
		return !passFail;
    }
    
    public String CPUTest(boolean passFail) {
		if (passFail == true) 
			return "Failed";
		else 
			return "Passed";
    }

    public String ROMTest(boolean passFail) {
		if (passFail == true) 
			return "Failed";
		else 
			return "Passed";
    }

    public String RAMTest(boolean passFail) {
		if (passFail == true) 
			return "Failed";
		else 
			return "Passed";
    }

    // Form Variables declaration
    private javax.swing.JPanel jPanel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel diagram;
    private javax.swing.JButton doneButton;
    private javax.swing.JCheckBox powerOnCheckbox;
    private javax.swing.JCheckBox videoCheckbox;
    private javax.swing.JCheckBox keyboardCheckbox;
    private javax.swing.JCheckBox CPUCheckbox;
    private javax.swing.JCheckBox RAMCheckbox;
    private javax.swing.JCheckBox ROMCheckbox;
    private javax.swing.JFrame parent;
    private javax.swing.JDialog dialog;
    // End of form variables declaration


    /**
     * Purpose    : The main method can be used to run this example directly from Java. 
     * Parameters : args - The location of the TestStand root folder as the first argument 
     */
    public static void main(String args[]) {

		if (args.length != 1)
			System.out.println("Please pass the location of the TestStand installation folder as the only argument.");
		else
			start(args[0]);
    }

    /**
     * Purpose    : The start method can be used to run this example directly from Java. 
     * Parameters : Path - The location of the TestStand root folder
     */
     public static void start(String path) {
    	  new Computer(path);
    }
}
