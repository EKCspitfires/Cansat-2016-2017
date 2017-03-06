Imports System.IO.Ports
Public Class Form1
    Dim WithEvents sp As New SerialPort

    Private Sub GetSerialPortNames()
        For Each sport As String In My.Computer.Ports.SerialPortNames
            cmbPort.Items.Add(sport)
        Next
    End Sub

    Sub ShowString(ByVal myString As String)
        txtIn.AppendText(myString)
    End Sub

    Delegate Sub myMethodDelegate(ByVal [text] As String)
    Dim myDelegate As New myMethodDelegate(AddressOf ShowString)

    Private Sub Form1_Load(sender As System.Object, e As EventArgs) Handles MyBase.Load
        Dim BaudRates() As String = {"300", "1200", "2400", "4800", "9600", "14400", "19200", "28800", "38400", "57600", "115200"}
        cmbBaud.Items.AddRange(BaudRates)
        cmbBaud.SelectedIndex = 4
        Try
            GetSerialPortNames()
            cmbPort.SelectedIndex = 0
        Catch
            MsgBox("No ports connected.")
        End Try
    End Sub

    Private Function BaudRates() As Object
        Throw New NotImplementedException()
    End Function

    Private Sub btnConnect_Click(sender As Object, e As EventArgs) Handles btnConnect.Click
        Try
            sp.BaudRate = cmbBaud.SelectedItem.ToString
            sp.PortName = cmbPort.SelectedItem.ToString
            sp.Open()
            If sp.IsOpen Then
                btnConnect.Visible = False
                cmbPort.Enabled = False
                cmbBaud.Enabled = False
                btnDisconnect.Visible = True
            End If
        Catch
            sp.Close()
        End Try
    End Sub

    Private Sub btnDisconnect_Click(sender As Object, e As EventArgs) Handles btnDisconnect.Click
        Try
            sp.Close()
            btnConnect.Visible = True
            btnDisconnect.Visible = False
            cmbPort.Enabled = True
            cmbBaud.Enabled = True
            Exit Sub
        Catch
            MessageBox.Show("Some kind of problem.")
        End Try
    End Sub

    Private Sub Form1_FormClosing(sender As Object, e As FormClosingEventArgs) Handles MyBase.FormClosing
        If sp.IsOpen() Then
            MessageBox.Show("Disconnect before closing")
            e.Cancel = True
        End If
    End Sub
    Private Sub SerialPort_DataReceived(ByVal sender As Object, ByVal e As System.IO.Ports.SerialDataReceivedEventArgs) Handles sp.DataReceived
        Dim str As String = sp.ReadExisting()
        Invoke(myDelegate, str)
    End Sub

    Private Sub btnSend_Click(sender As Object, e As EventArgs) Handles btnSend.Click
        If sp.IsOpen() Then
            sp.WriteLine(txtMessage.Text)
            txtMessage.Text = ""
        End If
    End Sub

End Class
