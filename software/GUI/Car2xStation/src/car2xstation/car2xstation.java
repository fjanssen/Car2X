/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package car2xstation;

import java.awt.Color;
import java.net.*;
import java.io.*;
import java.awt.KeyEventDispatcher;
import java.awt.KeyboardFocusManager;
import java.awt.event.KeyEvent;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author HS
 */
public class car2xstation extends javax.swing.JFrame {
    
    private static boolean remoteMode=false;
    private static boolean toSendb=false;
    private static int counter=0;
    private static boolean waitforconf=false;
    public Runnable form;
    public Runnable running;
    private static boolean[] pressed={false,false,false,false};                 //WASD
    
    
    // Connect status constants
    public final static int NULL = 0;
    public final static int DISCONNECTED = 1;
    public final static int DISCONNECTING = 2;
    public final static int BEGINCONNECT = 3;
    public final static int CONNECTED = 4;
    public final static String statusMessages[] = {
        " Error while connecting!", " Disconnected",
        " Disconnecting...", " Connecting...", " Connected"
    };
    public final static String END_CHAT_SESSION
            = new Character((char) 0).toString();

    // Connection state info
    //public static String hostIP = "10.10.100.105";
    public static String hostIP = "127.0.0.1";
    public static int port = 23;
    public static String myIP0x="7F000001";
    public static int connectionStatus = DISCONNECTED;
    public static String statusString = statusMessages[connectionStatus];
    public static StringBuffer toAppend = new StringBuffer("");
    public static byte[] toSend = new byte[1];

    // TCP Components
    public static Socket socket = null;
    public static InputStream in = null;
    public static DataOutputStream out = null;
    public int messageID;
    public int packageNumber = 1;
    public String messageText;
    public String idStr;
    public static sendingUnit sendingUnit = new sendingUnit();
    public static String[] msgStrings = sendingUnit.getStrings();

   //functions
    public static boolean[] isPressed(){
        synchronized (car2xstation.class){
            return pressed;
        }
    }
    
    private static void appendToChatBox(String s) {
        synchronized (toAppend) {
            toAppend.append(s);
        }
    }
    
    private static void senduBytes(ubyte[] msg) {
        synchronized (toSend) {
            toSend=new byte[msg.length];
            String pri="msg: ";
            for(int i =0; i<msg.length;i++){
                toSend[i]=msg[i].tosByte();
                pri+=msg[i].toString();
            }
            System.out.println(pri);
            toSendb=true;
        }
    }

    private static void changeStatusTS(int newConnectStatus, boolean noError, Runnable form) {
        // Change state if valid state
        if (newConnectStatus != NULL) {
            connectionStatus = newConnectStatus;
        }

        // If there is no error, display the appropriate status message
        if (noError) {
            statusString = statusMessages[connectionStatus];
        } // Otherwise, display error message
        else {
            statusString = statusMessages[NULL];
        }

      // Call the run() routine (Runnable interface) on the
        // error-handling and GUI-update thread
        form.run();
    }

    // Cleanup for disconnect
    private static void cleanUp() throws IOException {
        try {
            if (socket != null) {
                socket.close();
                socket = null;
            }
        } catch (IOException e) {
            socket = null;
        }   
        try {
            if (in != null) {
                in.close();
                in = null;
            }
        } catch (IOException e) {
            in = null;
        }

        if (out != null) {
            out.close();
            out = null;
        }
    }

    /**
     * Creates new form car2xstation
     */
    public car2xstation() {
        form = new Runnable() {
            public void run() {
                switch (connectionStatus) {
                    case DISCONNECTED:
                        jButton1.disable();
                        break;

                    case DISCONNECTING:
                        jButton1.disable();
                        break;

                    case CONNECTED:
                        jButton1.enable();
                        break;

                    case BEGINCONNECT:
                        jButton1.disable(); 
                        break;
                }
      // Make sure that the button/text field states are consistent
                // with the internal states

            }
        };
            running=new Runnable(){
            public void run(){
            String s="";
            String msg="";
            String finalMsg="";
            int msgStart=-1;
            int headerLength=18;
            int payloadLength=0;
             // Receive data
            while(true){
            try {
                if(in!=null){         
                int inp=in.read();
                System.out.println("inp: "+inp);
                if(inp<0){
                    //inp=
                }
                s=Integer.toHexString(inp);
                    while(s.length()<2){
                    s="0"+s;
                }
                System.out.printf("s: 0x"+s+"\n");
                msg+=s;
                }else{
                    try { // Poll every ~10 ms
                Thread.sleep(40);
                } catch (InterruptedException e) {
                }
                }
                } catch (IOException ex) {
                Logger.getLogger(car2xstation.class.getName()).log(Level.SEVERE, null, ex);
                }
                if (msg!=null&&msg.length()>7&&msgStart==-1) {
                            System.out.printf("CARP recieved\n");
                            msgStart=msg.indexOf("43415250");
                            
                }
                if(msg!=null&&msgStart>=0&&(msg.length()-msgStart)==32){
                    payloadLength=Integer.parseInt(msg.substring(msgStart+24, msgStart+32), 16);
                    System.out.printf("header recieved. pl: %d\n",payloadLength);
                }
                if(msg!=null&&msgStart>=0&&msg.length()-msgStart>35+payloadLength*2){
                    System.out.printf("complete msg recieved\n");
                    finalMsg=msg.substring(msgStart, msgStart+36+payloadLength*2);
                    msgStart=-1;
                    payloadLength=0;
                    msg="";
                }
                if(finalMsg.length()>0){
                    System.out.printf("msg printed\n");
                    String out="";
                    for(int i=0;i<finalMsg.length();i++){
                    if(i%2==0){
                        out+="x"+finalMsg.charAt(i);
                    }    else{
                        out+=finalMsg.charAt(i);
                    }
                    }
                    appendToChatBox("MSG: \n" + out + "\n");
                    finalMsg="";
                }
            }
        }
        };

        new Thread(running).start();

        initComponents();
        jComboBox1.removeAllItems();
        for (int i = 0; i < msgStrings.length; i++) {
            jComboBox1.insertItemAt(msgStrings[i], i);
        }
        java.awt.EventQueue.invokeLater(form);
        this.setVisible(true);
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jComboBox1 = new javax.swing.JComboBox();
        jButton1 = new javax.swing.JButton();
        jTextField1 = new javax.swing.JTextField();
        jScrollPane1 = new javax.swing.JScrollPane();
        jTextArea1 = new javax.swing.JTextArea();
        jToggleButton1 = new javax.swing.JToggleButton();
        jToggleButton2 = new javax.swing.JToggleButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setPreferredSize(new java.awt.Dimension(960, 540));

        jComboBox1.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "Item 1", "Item 2", "Item 3", "Item 4" }));
        jComboBox1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jComboBox1ActionPerformed(evt);
            }
        });

        jButton1.setText("Send");
        jButton1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton1ActionPerformed(evt);
            }
        });

        jTextField1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jTextField1ActionPerformed(evt);
            }
        });

        jTextArea1.setEditable(false);
        jTextArea1.setColumns(20);
        jTextArea1.setRows(5);
        jScrollPane1.setViewportView(jTextArea1);

        jToggleButton1.setText("Connect");
        jToggleButton1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jToggleButton1ActionPerformed(evt);
            }
        });

        jToggleButton2.setForeground(new java.awt.Color(255, 0, 51));
        jToggleButton2.setText("RC Mode Off");
        jToggleButton2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jToggleButton2ActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                        .addGap(11, 11, 11)
                        .addComponent(jToggleButton1, javax.swing.GroupLayout.PREFERRED_SIZE, 105, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(0, 0, Short.MAX_VALUE))
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                        .addContainerGap()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(jScrollPane1, javax.swing.GroupLayout.Alignment.TRAILING)
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(jComboBox1, javax.swing.GroupLayout.PREFERRED_SIZE, 137, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jTextField1))
                            .addGroup(layout.createSequentialGroup()
                                .addGap(132, 132, 132)
                                .addComponent(jButton1, javax.swing.GroupLayout.PREFERRED_SIZE, 106, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(30, 30, 30)
                                .addComponent(jToggleButton2)
                                .addGap(0, 7, Short.MAX_VALUE)))))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 327, Short.MAX_VALUE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jTextField1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jComboBox1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(16, 16, 16)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jButton1)
                    .addComponent(jToggleButton1)
                    .addComponent(jToggleButton2))
                .addGap(7, 7, 7))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void jComboBox1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jComboBox1ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_jComboBox1ActionPerformed

    private void jToggleButton1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jToggleButton1ActionPerformed
        if (connectionStatus != CONNECTED && connectionStatus != BEGINCONNECT) {
            jToggleButton1.setLabel("Disconnect");
            connectionStatus = BEGINCONNECT;
        } else {
            jToggleButton1.setLabel("Connect");
            
            //TODO: send RC reset message
            jToggleButton2.setLabel("RC Mode Off");
            jToggleButton2.setForeground(Color.red);
            waitforconf=false;
            remoteMode=false;
            
            System.out.println("close RCmode\n");
            //give away RC
            //header
                        ubyte[] header=new ubyte[6];
                        header[0]=new ubyte('C');
                        header[1]=new ubyte('A');
                        header[2]=new ubyte('R');
                        header[3]=new ubyte('P');
                        header[4]=new ubyte(0xFF&(packageNumber/256));
                        header[5]=new ubyte(0xFF&packageNumber);
                         //let sendingUnit work...
                        senduBytes(sendingUnit.getRC(header,false));
                        //increase packageNumber
                        packageNumber++;
                        if (packageNumber > 65535) {
                        packageNumber = 1;
                        }
                        
                        connectionStatus = DISCONNECTING;
        }
    }//GEN-LAST:event_jToggleButton1ActionPerformed

    private void jButton1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton1ActionPerformed
        if (sendingUnit != null && connectionStatus == CONNECTED) {
            messageText = jTextField1.getText();
            if(messageText==null||messageText.length()<1)messageText="0";
            //packageNumber as string
            ubyte[] header=new ubyte[6];
            header[0]=new ubyte('C');
            header[1]=new ubyte('A');
            header[2]=new ubyte('R');
            header[3]=new ubyte('P');
            header[4]=new ubyte(0xFF&(packageNumber/256));
            header[5]=new ubyte(0xFF&packageNumber);
            System.out.println("pkgn: "+packageNumber);
            //select message
            messageID = jComboBox1.getSelectedIndex();
            //let sendingUnit work...
            senduBytes(sendingUnit.sendMessage(messageID, messageText, header));
            //increase package Number
            packageNumber++;
            if (packageNumber > 65535) {
                packageNumber = 1;
            }
        }
    }//GEN-LAST:event_jButton1ActionPerformed

    private void jTextField1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jTextField1ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_jTextField1ActionPerformed

    private void jToggleButton2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jToggleButton2ActionPerformed
        if (connectionStatus == CONNECTED && !remoteMode) {
            //TODO: send RC message with own ip 
            jToggleButton2.setLabel("RC Mode On");
            jToggleButton2.setForeground(Color.green);
            //send RC-Msg to gain control
                    
                        //header
                        ubyte[] header=new ubyte[6];
                        header[0]=new ubyte('C');
                        header[1]=new ubyte('A');
                        header[2]=new ubyte('R');
                        header[3]=new ubyte('P');
                        header[4]=new ubyte(0xFF&(packageNumber/256));
                        header[5]=new ubyte(0xFF&packageNumber);
                         //let sendingUnit work...
                        senduBytes(sendingUnit.getRC(header,true));
                        //increase packageNumber
                        packageNumber++;
                        if (packageNumber > 65535) {
                        packageNumber = 1;
                        }
            
            //wait for ok response msg from car
                        waitforconf=true;
                        counter=0;
        } else {
            jToggleButton2.setLabel("RC Mode Off");
            jToggleButton2.setForeground(Color.red);
            waitforconf=false;
            remoteMode=false;
            //give away the control
            
            //header
                        ubyte[] header=new ubyte[6];
                        header[0]=new ubyte('C');
                        header[1]=new ubyte('A');
                        header[2]=new ubyte('R');
                        header[3]=new ubyte('P');
                        header[4]=new ubyte(0xFF&(packageNumber/256));
                        header[5]=new ubyte(0xFF&packageNumber);
                         //let sendingUnit work...
                        senduBytes(sendingUnit.getRC(header,false));
                        //increase packageNumber
                        packageNumber++;
                        if (packageNumber > 65535) {
                        packageNumber = 1;
                        }
        }
    }//GEN-LAST:event_jToggleButton2ActionPerformed

    
    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) throws IOException {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(car2xstation.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(car2xstation.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(car2xstation.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(car2xstation.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        final car2xstation station = new car2xstation();
        Runnable form = station.form;
        
        //key listeer stuff
        KeyboardFocusManager.getCurrentKeyboardFocusManager().addKeyEventDispatcher(new KeyEventDispatcher() {

            @Override
            public boolean dispatchKeyEvent(KeyEvent ke) {
                synchronized(car2xstation.class){
                    switch(ke.getID()){
                        case KeyEvent.KEY_PRESSED:
                            switch(ke.getKeyCode()){
                                case KeyEvent.VK_W:
                                    pressed[0]=true;
                                    break;
                                    case KeyEvent.VK_A:
                                    pressed[1]=true;
                                    break;
                                    case KeyEvent.VK_S:
                                    pressed[2]=true;
                                    break;
                                    case KeyEvent.VK_D:
                                    pressed[3]=true;
                                    break;
                                    default:
                                    break;
                            }
                        break;
                            case KeyEvent.KEY_RELEASED:
                                switch(ke.getKeyCode()){
                                case KeyEvent.VK_W:
                                    pressed[0]=false;
                                    break;
                                    case KeyEvent.VK_A:
                                    pressed[1]=false;
                                    break;
                                    case KeyEvent.VK_S:
                                    pressed[2]=false;
                                    break;
                                    case KeyEvent.VK_D:
                                    pressed[3]=false;
                                    break;
                                    default:
                                    break;
                            }
                        break;
                            default:
                        break;                                       
                    }
                    return false;
                }
            }
        });   

        String s;
        
        while (true) {
            try { // Poll every ~10 ms
                Thread.sleep(10);
            } catch (InterruptedException e) {
            }

            //update incoming message window
            station.jTextArea1.setText(toAppend.toString());
            
            switch (connectionStatus) {
                case BEGINCONNECT:
                    try {
                        // Try to connect
                        socket = new Socket(hostIP, port);
                        in = socket.getInputStream();
                        out = new DataOutputStream(socket.getOutputStream());
                        changeStatusTS(CONNECTED, true, form);
                    } // If error, clean up and output an error message
                    catch (IOException e) {
                        cleanUp();
                        changeStatusTS(DISCONNECTED, false, form);
                    }
                    break;

                case CONNECTED:
                    try {
                        //remote control mode
                        if(remoteMode){
                        //evaluate pressed keys    
                        station.messageText = "00000000";
                        if(isPressed()[0]) station.messageText="FF000000";
                        if(isPressed()[1]) station.messageText=station.messageText.substring(0,2)+"FF0000";
                        if(isPressed()[2]) station.messageText=station.messageText.substring(0,4)+"FF00";
                        if(isPressed()[3]) station.messageText=station.messageText.substring(0,6)+"FF";
                        //header
                        ubyte[] header=new ubyte[6];
                        header[0]=new ubyte('C');
                        header[1]=new ubyte('A');
                        header[2]=new ubyte('R');
                        header[3]=new ubyte('P');
                        header[4]=new ubyte(0xFF&(station.packageNumber/256));
                        header[5]=new ubyte(0xFF&station.packageNumber);
                         //let sendingUnit work...
                        station.senduBytes(station.sendingUnit.doRC(station.messageText, header));
                        //increase packageNumber
                        station.packageNumber++;
                        if (station.packageNumber > 65535) {
                        station.packageNumber = 1;
                        }
                        }    
                        
                        // Send data
                        if (toSendb) {
                            System.out.println("sending...\n");
                            out.write(toSend);
                            out.flush();
                            toSendb=false;
                            toSend=new byte[1];
                            changeStatusTS(NULL, true, form);
                        }

                       
                        if(waitforconf){
                            //TODO: integrate confirmation of rc
                            if(counter>500)remoteMode=true;
                            counter++;
                        }
                    } catch (IOException e) {
                        cleanUp();
                        changeStatusTS(DISCONNECTED, false, form);
                    }
                    break;

                case DISCONNECTING:
                    //Clean up (close all streams/sockets)
                    cleanUp();
                    changeStatusTS(DISCONNECTED, true, form);
                    break;

                default:
                    break; // do nothing
            }
        }
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton jButton1;
    private javax.swing.JComboBox jComboBox1;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JTextArea jTextArea1;
    private javax.swing.JTextField jTextField1;
    private javax.swing.JToggleButton jToggleButton1;
    private javax.swing.JToggleButton jToggleButton2;
    // End of variables declaration//GEN-END:variables
}
