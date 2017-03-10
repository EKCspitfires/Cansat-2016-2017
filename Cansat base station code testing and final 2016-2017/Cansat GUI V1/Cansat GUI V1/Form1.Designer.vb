<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()>
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()>
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()>
    Private Sub InitializeComponent()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Form1))
        Me.cmbPort = New System.Windows.Forms.ComboBox()
        Me.GroupBox1 = New System.Windows.Forms.GroupBox()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.btnDisconnect = New System.Windows.Forms.Button()
        Me.btnConnect = New System.Windows.Forms.Button()
        Me.cmbBaud = New System.Windows.Forms.ComboBox()
        Me.txtIn = New System.Windows.Forms.TextBox()
        Me.txtMessage = New System.Windows.Forms.TextBox()
        Me.btnSend = New System.Windows.Forms.Button()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.aXTxt = New System.Windows.Forms.TextBox()
        Me.VTxt = New System.Windows.Forms.TextBox()
        Me.PTxt = New System.Windows.Forms.TextBox()
        Me.TTxt = New System.Windows.Forms.TextBox()
        Me.NTxt = New System.Windows.Forms.TextBox()
        Me.LATxt = New System.Windows.Forms.TextBox()
        Me.LOTxt = New System.Windows.Forms.TextBox()
        Me.gZTxt = New System.Windows.Forms.TextBox()
        Me.gYTxt = New System.Windows.Forms.TextBox()
        Me.gXTxt = New System.Windows.Forms.TextBox()
        Me.aYTxt = New System.Windows.Forms.TextBox()
        Me.aZTxt = New System.Windows.Forms.TextBox()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.Label5 = New System.Windows.Forms.Label()
        Me.Label6 = New System.Windows.Forms.Label()
        Me.Label7 = New System.Windows.Forms.Label()
        Me.Label8 = New System.Windows.Forms.Label()
        Me.Label9 = New System.Windows.Forms.Label()
        Me.Label10 = New System.Windows.Forms.Label()
        Me.Label11 = New System.Windows.Forms.Label()
        Me.Label12 = New System.Windows.Forms.Label()
        Me.Label14 = New System.Windows.Forms.Label()
        Me.Label15 = New System.Windows.Forms.Label()
        Me.Label13 = New System.Windows.Forms.Label()
        Me.GroupBox1.SuspendLayout()
        Me.SuspendLayout()
        '
        'cmbPort
        '
        Me.cmbPort.FormattingEnabled = True
        Me.cmbPort.Location = New System.Drawing.Point(6, 42)
        Me.cmbPort.Name = "cmbPort"
        Me.cmbPort.Size = New System.Drawing.Size(121, 24)
        Me.cmbPort.TabIndex = 0
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.Label2)
        Me.GroupBox1.Controls.Add(Me.Label1)
        Me.GroupBox1.Controls.Add(Me.btnDisconnect)
        Me.GroupBox1.Controls.Add(Me.btnConnect)
        Me.GroupBox1.Controls.Add(Me.cmbBaud)
        Me.GroupBox1.Controls.Add(Me.cmbPort)
        Me.GroupBox1.Location = New System.Drawing.Point(12, 35)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(447, 100)
        Me.GroupBox1.TabIndex = 1
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = "Connection"
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(163, 22)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(65, 17)
        Me.Label2.TabIndex = 5
        Me.Label2.Text = "baudrate"
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(43, 22)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(34, 17)
        Me.Label1.TabIndex = 4
        Me.Label1.Text = "com"
        '
        'btnDisconnect
        '
        Me.btnDisconnect.Location = New System.Drawing.Point(341, 44)
        Me.btnDisconnect.Name = "btnDisconnect"
        Me.btnDisconnect.Size = New System.Drawing.Size(98, 23)
        Me.btnDisconnect.TabIndex = 3
        Me.btnDisconnect.Text = "Disconnect"
        Me.btnDisconnect.UseVisualStyleBackColor = True
        '
        'btnConnect
        '
        Me.btnConnect.Location = New System.Drawing.Point(260, 43)
        Me.btnConnect.Name = "btnConnect"
        Me.btnConnect.Size = New System.Drawing.Size(75, 23)
        Me.btnConnect.TabIndex = 2
        Me.btnConnect.Text = "Connect"
        Me.btnConnect.UseVisualStyleBackColor = True
        '
        'cmbBaud
        '
        Me.cmbBaud.FormattingEnabled = True
        Me.cmbBaud.Location = New System.Drawing.Point(133, 42)
        Me.cmbBaud.Name = "cmbBaud"
        Me.cmbBaud.Size = New System.Drawing.Size(121, 24)
        Me.cmbBaud.TabIndex = 1
        '
        'txtIn
        '
        Me.txtIn.Location = New System.Drawing.Point(12, 166)
        Me.txtIn.Multiline = True
        Me.txtIn.Name = "txtIn"
        Me.txtIn.ScrollBars = System.Windows.Forms.ScrollBars.Vertical
        Me.txtIn.Size = New System.Drawing.Size(447, 100)
        Me.txtIn.TabIndex = 2
        '
        'txtMessage
        '
        Me.txtMessage.Location = New System.Drawing.Point(93, 273)
        Me.txtMessage.Name = "txtMessage"
        Me.txtMessage.Size = New System.Drawing.Size(366, 22)
        Me.txtMessage.TabIndex = 3
        '
        'btnSend
        '
        Me.btnSend.Location = New System.Drawing.Point(12, 272)
        Me.btnSend.Name = "btnSend"
        Me.btnSend.Size = New System.Drawing.Size(75, 23)
        Me.btnSend.TabIndex = 4
        Me.btnSend.Text = "Send"
        Me.btnSend.UseVisualStyleBackColor = True
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(12, 146)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(240, 17)
        Me.Label3.TabIndex = 6
        Me.Label3.Text = "aX,aY,aZ,gX,gY,gZ,LO,LA,N,T,P,V,A"
        '
        'aXTxt
        '
        Me.aXTxt.Location = New System.Drawing.Point(49, 312)
        Me.aXTxt.Name = "aXTxt"
        Me.aXTxt.Size = New System.Drawing.Size(99, 22)
        Me.aXTxt.TabIndex = 7
        '
        'VTxt
        '
        Me.VTxt.Location = New System.Drawing.Point(329, 452)
        Me.VTxt.Name = "VTxt"
        Me.VTxt.Size = New System.Drawing.Size(99, 22)
        Me.VTxt.TabIndex = 9
        '
        'PTxt
        '
        Me.PTxt.Location = New System.Drawing.Point(329, 424)
        Me.PTxt.Name = "PTxt"
        Me.PTxt.Size = New System.Drawing.Size(99, 22)
        Me.PTxt.TabIndex = 10
        '
        'TTxt
        '
        Me.TTxt.Location = New System.Drawing.Point(329, 396)
        Me.TTxt.Name = "TTxt"
        Me.TTxt.Size = New System.Drawing.Size(99, 22)
        Me.TTxt.TabIndex = 11
        '
        'NTxt
        '
        Me.NTxt.Location = New System.Drawing.Point(329, 368)
        Me.NTxt.Name = "NTxt"
        Me.NTxt.Size = New System.Drawing.Size(99, 22)
        Me.NTxt.TabIndex = 12
        '
        'LATxt
        '
        Me.LATxt.Location = New System.Drawing.Point(329, 340)
        Me.LATxt.Name = "LATxt"
        Me.LATxt.Size = New System.Drawing.Size(99, 22)
        Me.LATxt.TabIndex = 13
        '
        'LOTxt
        '
        Me.LOTxt.Location = New System.Drawing.Point(329, 312)
        Me.LOTxt.Name = "LOTxt"
        Me.LOTxt.Size = New System.Drawing.Size(99, 22)
        Me.LOTxt.TabIndex = 14
        '
        'gZTxt
        '
        Me.gZTxt.Location = New System.Drawing.Point(49, 452)
        Me.gZTxt.Name = "gZTxt"
        Me.gZTxt.Size = New System.Drawing.Size(99, 22)
        Me.gZTxt.TabIndex = 15
        '
        'gYTxt
        '
        Me.gYTxt.Location = New System.Drawing.Point(49, 424)
        Me.gYTxt.Name = "gYTxt"
        Me.gYTxt.Size = New System.Drawing.Size(99, 22)
        Me.gYTxt.TabIndex = 16
        '
        'gXTxt
        '
        Me.gXTxt.Location = New System.Drawing.Point(49, 396)
        Me.gXTxt.Name = "gXTxt"
        Me.gXTxt.Size = New System.Drawing.Size(99, 22)
        Me.gXTxt.TabIndex = 17
        '
        'aYTxt
        '
        Me.aYTxt.Location = New System.Drawing.Point(49, 340)
        Me.aYTxt.Name = "aYTxt"
        Me.aYTxt.Size = New System.Drawing.Size(99, 22)
        Me.aYTxt.TabIndex = 18
        '
        'aZTxt
        '
        Me.aZTxt.Location = New System.Drawing.Point(49, 368)
        Me.aZTxt.Name = "aZTxt"
        Me.aZTxt.Size = New System.Drawing.Size(99, 22)
        Me.aZTxt.TabIndex = 19
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.Location = New System.Drawing.Point(303, 399)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(17, 34)
        Me.Label4.TabIndex = 20
        Me.Label4.Text = "T" & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10)
        '
        'Label5
        '
        Me.Label5.AutoSize = True
        Me.Label5.Location = New System.Drawing.Point(303, 368)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(18, 17)
        Me.Label5.TabIndex = 21
        Me.Label5.Text = "N"
        '
        'Label6
        '
        Me.Label6.AutoSize = True
        Me.Label6.Location = New System.Drawing.Point(296, 312)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(27, 17)
        Me.Label6.TabIndex = 22
        Me.Label6.Text = "LO"
        '
        'Label7
        '
        Me.Label7.AutoSize = True
        Me.Label7.Location = New System.Drawing.Point(18, 452)
        Me.Label7.Name = "Label7"
        Me.Label7.Size = New System.Drawing.Size(25, 17)
        Me.Label7.TabIndex = 23
        Me.Label7.Text = "gZ"
        '
        'Label8
        '
        Me.Label8.AutoSize = True
        Me.Label8.Location = New System.Drawing.Point(15, 424)
        Me.Label8.Name = "Label8"
        Me.Label8.Size = New System.Drawing.Size(25, 17)
        Me.Label8.TabIndex = 24
        Me.Label8.Text = "gY"
        '
        'Label9
        '
        Me.Label9.AutoSize = True
        Me.Label9.Location = New System.Drawing.Point(15, 396)
        Me.Label9.Name = "Label9"
        Me.Label9.Size = New System.Drawing.Size(25, 17)
        Me.Label9.TabIndex = 25
        Me.Label9.Text = "gX"
        '
        'Label10
        '
        Me.Label10.AutoSize = True
        Me.Label10.Location = New System.Drawing.Point(18, 368)
        Me.Label10.Name = "Label10"
        Me.Label10.Size = New System.Drawing.Size(25, 17)
        Me.Label10.TabIndex = 26
        Me.Label10.Text = "aZ"
        '
        'Label11
        '
        Me.Label11.AutoSize = True
        Me.Label11.Location = New System.Drawing.Point(18, 340)
        Me.Label11.Name = "Label11"
        Me.Label11.Size = New System.Drawing.Size(25, 17)
        Me.Label11.TabIndex = 27
        Me.Label11.Text = "aY"
        '
        'Label12
        '
        Me.Label12.AutoSize = True
        Me.Label12.Location = New System.Drawing.Point(18, 312)
        Me.Label12.Name = "Label12"
        Me.Label12.Size = New System.Drawing.Size(25, 17)
        Me.Label12.TabIndex = 28
        Me.Label12.Text = "aX"
        '
        'Label14
        '
        Me.Label14.AutoSize = True
        Me.Label14.Location = New System.Drawing.Point(258, 424)
        Me.Label14.Name = "Label14"
        Me.Label14.Size = New System.Drawing.Size(65, 17)
        Me.Label14.TabIndex = 30
        Me.Label14.Text = "Pressure"
        '
        'Label15
        '
        Me.Label15.AutoSize = True
        Me.Label15.Location = New System.Drawing.Point(284, 455)
        Me.Label15.Name = "Label15"
        Me.Label15.Size = New System.Drawing.Size(39, 17)
        Me.Label15.TabIndex = 31
        Me.Label15.Text = "Volts"
        '
        'Label13
        '
        Me.Label13.AutoSize = True
        Me.Label13.Location = New System.Drawing.Point(296, 340)
        Me.Label13.Name = "Label13"
        Me.Label13.Size = New System.Drawing.Size(25, 17)
        Me.Label13.TabIndex = 33
        Me.Label13.Text = "LA"
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(8.0!, 16.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(1343, 599)
        Me.Controls.Add(Me.Label13)
        Me.Controls.Add(Me.Label15)
        Me.Controls.Add(Me.Label14)
        Me.Controls.Add(Me.Label12)
        Me.Controls.Add(Me.Label11)
        Me.Controls.Add(Me.Label10)
        Me.Controls.Add(Me.Label9)
        Me.Controls.Add(Me.Label8)
        Me.Controls.Add(Me.Label7)
        Me.Controls.Add(Me.Label6)
        Me.Controls.Add(Me.Label5)
        Me.Controls.Add(Me.Label4)
        Me.Controls.Add(Me.aZTxt)
        Me.Controls.Add(Me.aYTxt)
        Me.Controls.Add(Me.gXTxt)
        Me.Controls.Add(Me.gYTxt)
        Me.Controls.Add(Me.gZTxt)
        Me.Controls.Add(Me.LOTxt)
        Me.Controls.Add(Me.LATxt)
        Me.Controls.Add(Me.NTxt)
        Me.Controls.Add(Me.TTxt)
        Me.Controls.Add(Me.PTxt)
        Me.Controls.Add(Me.VTxt)
        Me.Controls.Add(Me.aXTxt)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.btnSend)
        Me.Controls.Add(Me.txtMessage)
        Me.Controls.Add(Me.txtIn)
        Me.Controls.Add(Me.GroupBox1)
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.Name = "Form1"
        Me.Text = "low risk GUI v1"
        Me.GroupBox1.ResumeLayout(False)
        Me.GroupBox1.PerformLayout()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

    Friend WithEvents cmbPort As ComboBox
    Friend WithEvents GroupBox1 As GroupBox
    Friend WithEvents btnDisconnect As Button
    Friend WithEvents btnConnect As Button
    Friend WithEvents cmbBaud As ComboBox
    Friend WithEvents txtIn As TextBox
    Friend WithEvents txtMessage As TextBox
    Friend WithEvents btnSend As Button
    Friend WithEvents Label1 As Label
    Friend WithEvents Label2 As Label
    Friend WithEvents Label3 As Label
    Friend WithEvents aXTxt As TextBox
    Friend WithEvents VTxt As TextBox
    Friend WithEvents PTxt As TextBox
    Friend WithEvents TTxt As TextBox
    Friend WithEvents NTxt As TextBox
    Friend WithEvents LATxt As TextBox
    Friend WithEvents LOTxt As TextBox
    Friend WithEvents gZTxt As TextBox
    Friend WithEvents gYTxt As TextBox
    Friend WithEvents gXTxt As TextBox
    Friend WithEvents aYTxt As TextBox
    Friend WithEvents aZTxt As TextBox
    Friend WithEvents Label4 As Label
    Friend WithEvents Label5 As Label
    Friend WithEvents Label6 As Label
    Friend WithEvents Label7 As Label
    Friend WithEvents Label8 As Label
    Friend WithEvents Label9 As Label
    Friend WithEvents Label10 As Label
    Friend WithEvents Label11 As Label
    Friend WithEvents Label12 As Label
    Friend WithEvents Label14 As Label
    Friend WithEvents Label15 As Label
    Friend WithEvents Label13 As Label
End Class
