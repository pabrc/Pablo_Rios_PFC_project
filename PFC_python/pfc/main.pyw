# -*- coding: utf-8 -*-
"""
File: main.pyw

Description: This program allows you to configure the virtual intruments of a
                board in a remote way. To connect to the board is used the UDP
                protocol (server in port 80 and client in a random port).
                
                The configuration data (data field of the UDP packet) is defined
                in the file 'vi_protocol.py', which defines the different commands
                and data of the application protocol.

Created on Mon Oct 27 11:25:36 2014

@author: Pablo

"""

import sys                          # System functions
import socket                       # Network connection
import struct                       # Assemble/Disassemble packets
import time                         # To implement delays
import threading                    # To implement threads
from PyQt4.QtCore import *          # PyQt ...
from PyQt4.QtGui import *           # ...  modules
from PyQt4 import Qt, Qwt5          # QwtPlot (graphsignal)
from window import Ui_MainWindow    # User Interface
from vi_protocol import *           # VI_protocol


class Form(QMainWindow, Ui_MainWindow):

    #######################################################################
    ##                      Initialization functions                     ## 
    #######################################################################

    def __init__(self):
        super(Form, self).__init__()
        self.setupUi(self)      # recreates what we designed in Qt Designer
        self.initUi()
        self.graph_signal_init()     
        self.initTableFreq()
        
        self.write_text_browser_info("Initialization completed ... Please, "
                                     "specify IP and Port to connect to the "
                                     "server.")


    def initUi(self):
        """Initializes the user interface and connects the signals to the
        functions in order to handle the their changes.
        
        """
            
        # Disable buttons not enabled in the initialization   
        self.btndisconnect.setEnabled(False)
        self.numsamples.setEnabled(False)
        self.dintervalsamples.setEnabled(False)
        self.label_samples.setEnabled(False)
        self.label_interval.setEnabled(False)
      
        # Connection of all the user interface signals we need 
        self.connect(self.btnconnect, SIGNAL("clicked()"), self.handle_btnconnect)
        self.connect(self.btndisconnect, SIGNAL("clicked()"), self.handle_btndisconnect) 
        self.connect(self.menufileloadsignal, SIGNAL("triggered()"), self.handle_load_signal)
        self.connect(self.menufilesavetable, SIGNAL("triggered()"), self.handle_save_table)
        self.connect(self.menufilecleartable, SIGNAL("triggered()"), self.handle_clear_table)
        self.connect(self.btnconfigfm, SIGNAL("clicked()"), self.handle_btnconfigfm)
        self.connect(self.btnfreqrequest, SIGNAL("clicked()"), self.handle_btnfreqrequest)
        self.connect(self.checkboxfreqreq, SIGNAL("clicked()"), self.handle_checkboxfreqreq)
        self.connect(self.btnconfigfg, SIGNAL("clicked()"), self.handle_btnconfigfg)
        self.connect(self.cboxsignaltype, SIGNAL("currentIndexChanged(int)"), self.handle_cboxsignaltype)
        self.connect(self.numdutycycle, SIGNAL("valueChanged(int)"), self.handle_numdutycycle)
                        
        
    def graph_signal_init(self):
        """Initializes the grahp of the Function Generator.
        
        """
        
        # lists of the x and y values to be ploted
        self.xaxis = list(range(36)) # list 0-350 (step of 10)
        self.yaxis = list(bytearray(36))    # list 36 zeros
        
        # plot background and title
        self.graphsignal.setCanvasBackground(Qt.Qt.white)
        self.graphsignal.setTitle("Function Generator' Signal")
        
        # show right axis
        self.graphsignal.enableAxis(Qwt5.QwtPlot.yRight)   
        
        # titles of the axis
        self.graphsignal.setAxisTitle(Qwt5.QwtPlot.xBottom, "Degrees")
        self.graphsignal.setAxisTitle(Qwt5.QwtPlot.yRight, "Voltage (V)")
        self.graphsignal.setAxisTitle(Qwt5.QwtPlot.yLeft, "Value [0-255]")
        
        self.curve = Qwt5.QwtPlotCurve("Data") #Create a dataCurve to plot data (info and printing format)
        self.curve.attach(self.graphsignal)    #attach the wave to the plot
        self.curve.setPen(QPen(Qt.Qt.blue))    #set the color of the wave
        
        #Plot data and Replot
        self.plot_axis()
    
            
    def initTableFreq(self):
        """Initialize the parameters of the table of frequencies.
        
        """
        
        self.number_of_rows = 0
        self.tablefrequency.setColumnCount(4)
        self.tablefrequency.setRowCount(self.number_of_rows)

       
    #######################################################################
    ##             Functions to control the changes of the UI            ## 
    #######################################################################       
       
       
    def handle_btnconnect(self):
        """When the button 'Connect' is pressed we open a socket, and we launch
        the receive_pkt thread.
        
        """
        
        # Enable/Disable buttons of the connection
        self.btnconnect.setEnabled(False)
        self.btndisconnect.setEnabled(True)
        
        # Get data from the user interface
        self.serverip = str(self.textserverip.text())
        self.serverport = int(self.numserverport.value())
        self.remoteaddr = (self.serverip, self.serverport)

        
        try:
            # Open the socket
            self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            self.sock.bind(('', 0)) # to get the host (IP, port) now, instead when a packet is sent
            
            #print self.sock.getsockname()
            
            #data = assemble_packet([CMD_RESET])
            #bytes_sent = self.sock.sendto(data, self.remoteaddr)
            #print bytes_sent            
            
            self.rcv_activated = True   # it enables to create a reception socket in the
                                        #  reception thread
            
            # We launch the thread that allow us to receive packets from the server
            #  It is a child thread of the main thread
            self.thread_receive_pkt = threading.Thread(target = self.receive_pkt)
            self.thread_receive_pkt.start() 
            
            
            self.write_text_browser_info("Socket created ... ready to configure the "
                                   "board. Please, select the Virtual Instrument "
                                   "and its configuration.")
            
        except socket.error:
            
            # If a socket exception occurs, we close the socket and show an error
            self.sock.close()
            self.write_text_browser_error("Failed to create the socket.")
      

    def receive_pkt(self):
        """Function that is executed in a separeted thread in order to receive
        packets from the server.

        """ 
        
        try:
            # Receive loop
            while (self.rcv_activated == True):
                
                packet, addr = self.sock.recvfrom(40)  # receives 40 bytes, which is the fixed length of
                                                       #  VI_protocol packet
                
                fields = disassemble_packet(packet)
                
                if fields[0] == CMD_FREQ_ANSWER:
                                                    
                    # Put the frequency value received in a new row of the frequency table
                    self.number_of_rows += 1
                    self.tablefrequency.setRowCount(self.number_of_rows)
                    self.tablefrequency.setItem(self.number_of_rows -1, 0, QTableWidgetItem(str(self.number_of_rows -1)))
                    self.tablefrequency.setItem(self.number_of_rows -1, 1, QTableWidgetItem(str(fields[1])))
                    self.tablefrequency.setItem(self.number_of_rows -1, 2, QTableWidgetItem(time.strftime("%d/%m/%Y")))
                    self.tablefrequency.setItem(self.number_of_rows -1, 3, QTableWidgetItem(time.strftime("%H:%M:%S")))
               
                else:
                    
                    self.write_text_browser_error("Command received unknown!")
        
        except socket.error: # The socket is closed
        
            self.sock.close()
            self.write_text_browser_error("The socket is closed! Please, connect again")

   
    def handle_btndisconnect(self):
        """When the button 'Disconnect' is pressed we close the sockets that
        we had been created before.
        
        """

        # Close the socket
        self.sock.close()        
        
        # Disable the receive
        self.rcv_activated = False    
        
        # Enable/Disable buttons of the user interface
        self.btndisconnect.setEnabled(False)
        self.btnconnect.setEnabled(True)        
        
        self.write_text_browser_warning("'Disconnect' pressed... socket closed.")       
       

    def handle_load_signal(self):
        """If the signa Non-Square is selected, we load a signal to the
        Function Generator. When the 'File->Load signal' is pressed, it
        shows a dialog where the user can select the signal's file to be loaded.
        
        """
        
        # Generates a dialog to get the function generator' signal to be loaded
        filename = unicode(QFileDialog.getOpenFileName(self, 'Load Non-Square Signal', '', ".txt(*.txt)"))    
        
        if str(self.cboxsignaltype.currentText()) == 'Non-Square':
            
            try:
                # Take the data from the file
                fp = file(filename, 'r')
                
                self.xaxis = [] # clear the xaxis list
                self.yaxis = [] # clear the yaxis list
                
                for line in fp:
                    if line[0] == '#':
                        continue
                    else:
                        x = line.split()
                        self.xaxis.append(int(x[0]))
                        self.yaxis.append(int(x[1]))
                
                fp.close()
                
                # Plot the signal with the new values of xaxis and yaxis
                self.plot_axis() 
                
            except:
                
                self.write_text_browser_error("You have not selected a Non-Square signal!")
        
    
    def plot_axis(self):
        """Plot the signal (self.xaxis, self.yaxis) in the grahp.
        
        """
        
        for i in range(0, 36):
            
            self.xaxis[i] = self.xaxis[i]*10
        
        # Scale the axis deppending on the data
        self.graphsignal.setAxisScale(Qwt5.QwtPlot.xBottom, 0, 360, 40.0)
        self.graphsignal.setAxisScale(Qwt5.QwtPlot.yRight, min(self.yaxis)*(3.3/256), max(self.yaxis)*(3.3/256))
        self.graphsignal.setAxisScale(Qwt5.QwtPlot.yLeft, min(self.yaxis), max(self.yaxis))
        
        # Update data
        self.curve.setData(self.xaxis, self.yaxis)
        self.graphsignal.replot()        
        
       
    def handle_save_table(self):
        """Saves the current table in a *.csv file.

        """        

        # Generates a dialog to get the file's name 
        filename = unicode(QFileDialog.getSaveFileName(self, 'Save Table', '', ".csv(*.csv)"))    
        
        fcsv = file(filename, 'w')
        
        for currentRow in range(self.tablefrequency.rowCount()):
            
            a_0 = str(self.tablefrequency.item(currentRow, 0).text())
            a_1 = str(self.tablefrequency.item(currentRow, 1).text())
            a_2 = str(self.tablefrequency.item(currentRow, 2).text())
            a_3 = str(self.tablefrequency.item(currentRow, 3).text())
            
            fcsv.write("{0}, {1}, {2}, {3}\n".format(a_0, a_1, a_2, a_3))

        fcsv.close()            
            
            
    def handle_clear_table(self):
        """When 'File->Clear Table' is pressed, we clear the frequency table.
        
        """
        
        self.number_of_rows = 0
        self.tablefrequency.setColumnCount(4)
        self.tablefrequency.setRowCount(self.number_of_rows)
    
            
    def handle_btnconfigfm(self):
        """When the button 'Configure Frequency Meter' is pressed we send 
        to the server the following commands:
        
            - CMD_ACTIVATE_FREQ_METER
            - CMD_AV_? (SIMPLE, WEIGHTED or EXPONENTIAL)
            - CMD_NFREQ_NODES
        
        """
        
        # Get data from the user interface
        average_nodes = int(self.numaveragenodes.value())
        average_type = str(self.cboxaveragetype.currentText())
        
        try:
            
            # Activate Frequency Meter
            data = assemble_packet([CMD_ACTIVATE_FREQ_METER])
            bytes_sent = self.sock.sendto(data, self.remoteaddr)
            #print bytes_sent
            
            # Send type of average
            if average_type == 'Simple':  
                
                data = assemble_packet([CMD_AV_SIMPLE])
                
            elif average_type == 'Weighted':
                
                data = assemble_packet([CMD_AV_WEIGHTED])
            
            else: #average_type == 'Exponential'
                
                data = assemble_packet([CMD_AV_EXP])
                
            bytes_sent = self.sock.sendto(data, self.remoteaddr)
            #print bytes_sent
            
            # Send the number of average nodes
            data = assemble_packet([CMD_NFREQ_NODES, average_nodes])      
            bytes_sent = self.sock.sendto(data, self.remoteaddr)
            #print bytes_sent
        
            self.write_text_browser_info("Configuration sent ... : "
                                        "Frecuency Meter, Average type = '%s', "
                                        "Average nodes = %d" %(average_type, average_nodes)) 
        
        except socket.error: # The socket is closed
            
             self.write_text_browser_error("The socket is closed! Please, connect again.")
            
            
    def handle_btnfreqrequest(self):
        """When 'Frequency Request' is pressed, we send a packet to 
        the server in order to get the frequency that it's being measure by
        the frequency meter. 
        
        If 'Auto Request' is checked, we send 'Sample' number of packets with
        'Interval' seconds interval between packets.

        """        
        
        if self.checkboxfreqreq.isChecked():    # Auto request enable
            
            # We call a child thread to send this packets because it will be 
            #  suspended (with the sleep function) and we do not want to 
            #  suspend the main thread (as it would suspend the main window)
            
            
            self.thread_auto_request = threading.Thread(target = self.sending_auto_request, 
                                                   args = ([CMD_FREQ_REQUEST], 
                                                           self.numsamples.value(), 
                                                            self.dintervalsamples.value()))
            self.thread_auto_request.start() 
    
        else:                                   # Auto request disable
            
            try:
                
                data = assemble_packet([CMD_FREQ_REQUEST])      
                bytes_sent = self.sock.sendto(data, self.remoteaddr)
                #print bytes_sent
                self.write_text_browser_info("Frequency request has been sent")
                
            except socket.error: # The socket is closed
                
                 self.write_text_browser_error("The socket is closed! Please, connect again.")
                

    def sending_auto_request(self, my_list, num, delay):
        """Thread that is launch to send 'num' packets with a specific
        'delay' between them.
        
        The data of the packet is in the list 'my_list'.
         
        """
        
        i = 0
        try:
            
            while i < num:
                
                data = assemble_packet(my_list)      
                bytes_sent = self.sock.sendto(data, self.remoteaddr)
                i += 1
                #print bytes_sent
                self.write_text_browser_info("Frequency request (%d out of %d) has been sent" % (i, num))
                time.sleep(delay)
        
        except socket.error: # The socket is closed
            
            self.write_text_browser_error("The socket is closed! Please, connect again.")      
            
     
    def handle_checkboxfreqreq(self):
        """We enable or disable the auto request parameters deppending on the
        state of the checkbox.

        """        
        
        if self.checkboxfreqreq.isChecked():    # Auto request enable
            
            self.numsamples.setEnabled(True)
            self.dintervalsamples.setEnabled(True)
            self.label_samples.setEnabled(True)
            self.label_interval.setEnabled(True)
        
        else:                                   # Auto request disable
        
            self.numsamples.setEnabled(False)
            self.dintervalsamples.setEnabled(False)
            self.label_samples.setEnabled(False)
            self.label_interval.setEnabled(False)
            
       
    def handle_btnconfigfg(self):
        """When the button 'Configure Function Generator' is pressed, we send the
        following packets to the server:
        
        - CMD_ACTIVATE_FUNCTION_GENERATOR
        - CMD_FG_? (SQUARE or NON-SQUARE)
        - CMD_RAM_VALUES (only if Non-Square signal is selected)
        - CMD_FG_CHANGE_FREQ
        - CMD_CHANGE_TON (only if Square signal is selected)
        
        """
        
        # Get data from the user interface
        frequency = long(self.dnumfrequency.value())
        dcycle = long(self.numdutycycle.value())
        signal_type = str(self.cboxsignaltype.currentText())      
        
        try:
            
            # Activate Function Generator
            data = assemble_packet([CMD_ACTIVATE_FUNC_GEN])
            bytes_sent = self.sock.sendto(data, self.remoteaddr)
            #print bytes_sent
            
            # Send frequency
            data = assemble_packet([CMD_FG_CHANGE_FREQ, frequency])
            bytes_sent = self.sock.sendto(data, self.remoteaddr)
            #print bytes_sent
            
            if signal_type == 'Square':
                
                # Send Square signal
                data = assemble_packet([CMD_FG_SQUARE])
                bytes_sent = self.sock.sendto(data, self.remoteaddr)
                #print bytes_sent
                
                # Send Ton
                data = assemble_packet([CMD_FG_CHANGE_TON, dcycle])
                bytes_sent = self.sock.sendto(data, self.remoteaddr)
                #print bytes_sent
                
                self.write_text_browser_info("Configuration sent ... : "
                                            "Function Generator, '%s' signal, "
                                            "Frequency = %s Hz, DCycle = %s%%"
                                            %(signal_type, str(frequency), str(dcycle)))
               
            elif signal_type == 'Non-Square':
                            
                # Send Non-Square signal
                data = assemble_packet([CMD_FG_NON_SQUARE])
                bytes_sent = self.sock.sendto(data, self.remoteaddr)
                #print bytes_sent
                
                # Send the values of the Non-Square signal
                data = assemble_packet([CMD_RAM_VALUES] + self.yaxis)
                bytes_sent = self.sock.sendto(data, self.remoteaddr)
                #print bytes_sent
    
                self.write_text_browser_info("Configuration sent ... : "
                                            "Function Generator, '%s' signal, "
                                            "Frequency = %s Hz"
                                            %(signal_type, str(frequency)))
                
                self.write_text_browser_info("................................ "
                                             "RAM values = %s" % str(self.yaxis)) 
                   
            else:
                pass
                #raise 'ErrorSignalType'
        
        except socket.error: # The socket is closed
            
            self.write_text_browser_error("The socket is closed! Please, connect again.") 
        
       
    def handle_cboxsignaltype(self):
        """Enable or disable the duty cycle options.
         
        """
        
        if self.cboxsignaltype.currentText() == 'Square':
            
            # Duty Cycle enabled
            self.numdutycycle.setEnabled(True)
            self.labeldutycycle.setEnabled(True)
            self.handle_numdutycycle()
        
        elif self.cboxsignaltype.currentText() == 'Non-Square':
            
            # Duty Cycle disabled         
            self.numdutycycle.setEnabled(False)
            self.labeldutycycle.setEnabled(False)
            
            # We clear the graph 
            self.xaxis = list(range(36))        # list 0-35
            self.yaxis = list(bytearray(36))    # list 36 zeros
            self.plot_axis()
        

    def handle_numdutycycle(self):
        """If the user varies the duty cycle we refresh the signal in the graph.
        
        """
        
        dc = int(self.numdutycycle.value())
        
        self.xaxis = list(range(36))        # list 0-36
        self.yaxis = list(bytearray(36))    # list 36 zeros

        n_zeros = int(round((36.0/(100.0/dc))))
        
        for i in range(0, n_zeros):
            
            self.yaxis[i] = 255
        
        # Refresh the graph
        self.plot_axis()


    def write_text_browser_error(self, error):
        """Write ERROR in the text browser.
        
        """
        
        self.textbrowser.append("<font color=red>>> ERROR:</font> <font size=4 color=red> %s</font>" % error)
       
       
    def write_text_browser_warning(self, warning):
        """Write WARNING in the text browser.
        
        """
        
        self.textbrowser.append("<font color=blue>>> WARNING:</font> <font size=4 color=black> %s</font>" % warning)
       
       
    def write_text_browser_info(self, info):
        """Write INFO in the text browser.
        
        """
        
        self.textbrowser.append("<font color=green>>> INFO:</font> <font size=4 color=black> %s</font>" % info)
        


# Run the application
if __name__ == '__main__':
    app = QApplication(sys.argv)
    form = Form()
    form.show()
    sys.exit(app.exec_())



