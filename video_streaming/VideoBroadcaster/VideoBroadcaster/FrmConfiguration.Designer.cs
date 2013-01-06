namespace VideoBroadcaster
{
    partial class FrmConfiguration
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmConfiguration));
            this.tabMain = new System.Windows.Forms.TabControl();
            this.pageTranscoding = new System.Windows.Forms.TabPage();
            this.grpPredefined = new System.Windows.Forms.GroupBox();
            this.rbtnCustom = new System.Windows.Forms.RadioButton();
            this.rbtnWebm = new System.Windows.Forms.RadioButton();
            this.rbtnTs = new System.Windows.Forms.RadioButton();
            this.rbtnAsf = new System.Windows.Forms.RadioButton();
            this.rbtnMp4 = new System.Windows.Forms.RadioButton();
            this.grpTranscoding = new System.Windows.Forms.GroupBox();
            this.txtTranscoding = new System.Windows.Forms.TextBox();
            this.txtWarning = new System.Windows.Forms.TextBox();
            this.pageTool = new System.Windows.Forms.TabPage();
            this.grpTTranscoding = new System.Windows.Forms.GroupBox();
            this.txtTTranscoding = new System.Windows.Forms.TextBox();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnOK = new System.Windows.Forms.Button();
            this.grpTConversion = new System.Windows.Forms.GroupBox();
            this.txtOutput = new System.Windows.Forms.TextBox();
            this.lblOutput = new System.Windows.Forms.Label();
            this.progress = new System.Windows.Forms.ProgressBar();
            this.btnConvert = new System.Windows.Forms.Button();
            this.btnBrowse = new System.Windows.Forms.Button();
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.lblInput = new System.Windows.Forms.Label();
            this.txtInput = new System.Windows.Forms.TextBox();
            this.tabMain.SuspendLayout();
            this.pageTranscoding.SuspendLayout();
            this.grpPredefined.SuspendLayout();
            this.grpTranscoding.SuspendLayout();
            this.pageTool.SuspendLayout();
            this.grpTTranscoding.SuspendLayout();
            this.grpTConversion.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabMain
            // 
            this.tabMain.Controls.Add(this.pageTranscoding);
            this.tabMain.Controls.Add(this.pageTool);
            this.tabMain.Location = new System.Drawing.Point(12, 12);
            this.tabMain.Name = "tabMain";
            this.tabMain.SelectedIndex = 0;
            this.tabMain.Size = new System.Drawing.Size(678, 270);
            this.tabMain.TabIndex = 0;
            // 
            // pageTranscoding
            // 
            this.pageTranscoding.Controls.Add(this.grpPredefined);
            this.pageTranscoding.Controls.Add(this.grpTranscoding);
            this.pageTranscoding.Controls.Add(this.txtWarning);
            this.pageTranscoding.Location = new System.Drawing.Point(4, 22);
            this.pageTranscoding.Name = "pageTranscoding";
            this.pageTranscoding.Padding = new System.Windows.Forms.Padding(3);
            this.pageTranscoding.Size = new System.Drawing.Size(670, 244);
            this.pageTranscoding.TabIndex = 0;
            this.pageTranscoding.Text = "Transcoding";
            this.pageTranscoding.UseVisualStyleBackColor = true;
            // 
            // grpPredefined
            // 
            this.grpPredefined.Controls.Add(this.rbtnCustom);
            this.grpPredefined.Controls.Add(this.rbtnWebm);
            this.grpPredefined.Controls.Add(this.rbtnTs);
            this.grpPredefined.Controls.Add(this.rbtnAsf);
            this.grpPredefined.Controls.Add(this.rbtnMp4);
            this.grpPredefined.Location = new System.Drawing.Point(6, 144);
            this.grpPredefined.Name = "grpPredefined";
            this.grpPredefined.Size = new System.Drawing.Size(658, 94);
            this.grpPredefined.TabIndex = 5;
            this.grpPredefined.TabStop = false;
            this.grpPredefined.Text = "Preset Transcoding";
            // 
            // rbtnCustom
            // 
            this.rbtnCustom.AutoSize = true;
            this.rbtnCustom.Checked = true;
            this.rbtnCustom.Location = new System.Drawing.Point(523, 33);
            this.rbtnCustom.Name = "rbtnCustom";
            this.rbtnCustom.Size = new System.Drawing.Size(60, 17);
            this.rbtnCustom.TabIndex = 4;
            this.rbtnCustom.TabStop = true;
            this.rbtnCustom.Text = "Custom";
            this.rbtnCustom.UseVisualStyleBackColor = true;
            this.rbtnCustom.Click += new System.EventHandler(this.rbtnCustom_Click);
            // 
            // rbtnWebm
            // 
            this.rbtnWebm.AutoSize = true;
            this.rbtnWebm.Location = new System.Drawing.Point(279, 56);
            this.rbtnWebm.Name = "rbtnWebm";
            this.rbtnWebm.Size = new System.Drawing.Size(132, 17);
            this.rbtnWebm.TabIndex = 3;
            this.rbtnWebm.Text = "VP80 + Vorbis (Webm)";
            this.rbtnWebm.UseVisualStyleBackColor = true;
            this.rbtnWebm.Click += new System.EventHandler(this.rbtnWebm_Click);
            // 
            // rbtnTs
            // 
            this.rbtnTs.AutoSize = true;
            this.rbtnTs.Location = new System.Drawing.Point(279, 33);
            this.rbtnTs.Name = "rbtnTs";
            this.rbtnTs.Size = new System.Drawing.Size(108, 17);
            this.rbtnTs.TabIndex = 2;
            this.rbtnTs.Text = "H.264+ MP3 (TS)";
            this.rbtnTs.UseVisualStyleBackColor = true;
            this.rbtnTs.Click += new System.EventHandler(this.rbtnTs_Click);
            // 
            // rbtnAsf
            // 
            this.rbtnAsf.AutoSize = true;
            this.rbtnAsf.Location = new System.Drawing.Point(64, 56);
            this.rbtnAsf.Name = "rbtnAsf";
            this.rbtnAsf.Size = new System.Drawing.Size(120, 17);
            this.rbtnAsf.TabIndex = 1;
            this.rbtnAsf.Text = "WMV + WMA (ASF)";
            this.rbtnAsf.UseVisualStyleBackColor = true;
            this.rbtnAsf.Click += new System.EventHandler(this.rbtnAsf_Click);
            // 
            // rbtnMp4
            // 
            this.rbtnMp4.AutoSize = true;
            this.rbtnMp4.Location = new System.Drawing.Point(64, 33);
            this.rbtnMp4.Name = "rbtnMp4";
            this.rbtnMp4.Size = new System.Drawing.Size(119, 17);
            this.rbtnMp4.TabIndex = 0;
            this.rbtnMp4.Text = "H.264 + MP3 (MP4)";
            this.rbtnMp4.UseVisualStyleBackColor = true;
            this.rbtnMp4.Click += new System.EventHandler(this.rbtnMp4_Click);
            // 
            // grpTranscoding
            // 
            this.grpTranscoding.Controls.Add(this.txtTranscoding);
            this.grpTranscoding.Location = new System.Drawing.Point(6, 93);
            this.grpTranscoding.Name = "grpTranscoding";
            this.grpTranscoding.Size = new System.Drawing.Size(658, 45);
            this.grpTranscoding.TabIndex = 4;
            this.grpTranscoding.TabStop = false;
            this.grpTranscoding.Text = "Transcoding";
            // 
            // txtTranscoding
            // 
            this.txtTranscoding.Location = new System.Drawing.Point(6, 19);
            this.txtTranscoding.Name = "txtTranscoding";
            this.txtTranscoding.Size = new System.Drawing.Size(646, 20);
            this.txtTranscoding.TabIndex = 0;
            this.txtTranscoding.TextChanged += new System.EventHandler(this.txtTranscoding_TextChanged);
            this.txtTranscoding.KeyDown += new System.Windows.Forms.KeyEventHandler(this.txtTranscoding_KeyDown);
            // 
            // txtWarning
            // 
            this.txtWarning.Location = new System.Drawing.Point(6, 6);
            this.txtWarning.Multiline = true;
            this.txtWarning.Name = "txtWarning";
            this.txtWarning.ReadOnly = true;
            this.txtWarning.Size = new System.Drawing.Size(658, 81);
            this.txtWarning.TabIndex = 3;
            this.txtWarning.Text = resources.GetString("txtWarning.Text");
            // 
            // pageTool
            // 
            this.pageTool.Controls.Add(this.grpTConversion);
            this.pageTool.Controls.Add(this.grpTTranscoding);
            this.pageTool.Location = new System.Drawing.Point(4, 22);
            this.pageTool.Name = "pageTool";
            this.pageTool.Padding = new System.Windows.Forms.Padding(3);
            this.pageTool.Size = new System.Drawing.Size(670, 244);
            this.pageTool.TabIndex = 1;
            this.pageTool.Text = "Conversion Tool";
            this.pageTool.UseVisualStyleBackColor = true;
            // 
            // grpTTranscoding
            // 
            this.grpTTranscoding.Controls.Add(this.txtTTranscoding);
            this.grpTTranscoding.Location = new System.Drawing.Point(6, 6);
            this.grpTTranscoding.Name = "grpTTranscoding";
            this.grpTTranscoding.Size = new System.Drawing.Size(658, 68);
            this.grpTTranscoding.TabIndex = 0;
            this.grpTTranscoding.TabStop = false;
            this.grpTTranscoding.Text = "Transcoding";
            // 
            // txtTTranscoding
            // 
            this.txtTTranscoding.Enabled = false;
            this.txtTTranscoding.Location = new System.Drawing.Point(15, 28);
            this.txtTTranscoding.Name = "txtTTranscoding";
            this.txtTTranscoding.Size = new System.Drawing.Size(626, 20);
            this.txtTTranscoding.TabIndex = 0;
            // 
            // btnCancel
            // 
            this.btnCancel.Location = new System.Drawing.Point(611, 288);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(75, 23);
            this.btnCancel.TabIndex = 1;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = true;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // btnOK
            // 
            this.btnOK.Location = new System.Drawing.Point(530, 288);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(75, 23);
            this.btnOK.TabIndex = 2;
            this.btnOK.Text = "OK";
            this.btnOK.UseVisualStyleBackColor = true;
            this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
            // 
            // grpTConversion
            // 
            this.grpTConversion.Controls.Add(this.lblInput);
            this.grpTConversion.Controls.Add(this.txtInput);
            this.grpTConversion.Controls.Add(this.btnBrowse);
            this.grpTConversion.Controls.Add(this.btnConvert);
            this.grpTConversion.Controls.Add(this.progress);
            this.grpTConversion.Controls.Add(this.lblOutput);
            this.grpTConversion.Controls.Add(this.txtOutput);
            this.grpTConversion.Location = new System.Drawing.Point(6, 80);
            this.grpTConversion.Name = "grpTConversion";
            this.grpTConversion.Size = new System.Drawing.Size(658, 158);
            this.grpTConversion.TabIndex = 1;
            this.grpTConversion.TabStop = false;
            this.grpTConversion.Text = "Conversion";
            // 
            // txtOutput
            // 
            this.txtOutput.Location = new System.Drawing.Point(25, 76);
            this.txtOutput.Name = "txtOutput";
            this.txtOutput.Size = new System.Drawing.Size(616, 20);
            this.txtOutput.TabIndex = 0;
            this.txtOutput.TextChanged += new System.EventHandler(this.txtOutput_TextChanged);
            // 
            // lblOutput
            // 
            this.lblOutput.AutoSize = true;
            this.lblOutput.Location = new System.Drawing.Point(22, 60);
            this.lblOutput.Name = "lblOutput";
            this.lblOutput.Size = new System.Drawing.Size(42, 13);
            this.lblOutput.TabIndex = 1;
            this.lblOutput.Text = "Output:";
            // 
            // progress
            // 
            this.progress.Location = new System.Drawing.Point(25, 132);
            this.progress.Name = "progress";
            this.progress.Size = new System.Drawing.Size(616, 16);
            this.progress.TabIndex = 2;
            this.progress.Visible = false;
            // 
            // btnConvert
            // 
            this.btnConvert.Location = new System.Drawing.Point(566, 102);
            this.btnConvert.Name = "btnConvert";
            this.btnConvert.Size = new System.Drawing.Size(75, 23);
            this.btnConvert.TabIndex = 3;
            this.btnConvert.Text = "Start";
            this.btnConvert.UseVisualStyleBackColor = true;
            this.btnConvert.Click += new System.EventHandler(this.btnConvert_Click);
            // 
            // btnBrowse
            // 
            this.btnBrowse.Location = new System.Drawing.Point(485, 102);
            this.btnBrowse.Name = "btnBrowse";
            this.btnBrowse.Size = new System.Drawing.Size(75, 23);
            this.btnBrowse.TabIndex = 4;
            this.btnBrowse.Text = "Browse";
            this.btnBrowse.UseVisualStyleBackColor = true;
            this.btnBrowse.Click += new System.EventHandler(this.btnBrowse_Click);
            // 
            // timer
            // 
            this.timer.Interval = 1000;
            this.timer.Tick += new System.EventHandler(this.timer_Tick);
            // 
            // lblInput
            // 
            this.lblInput.AutoSize = true;
            this.lblInput.Location = new System.Drawing.Point(22, 21);
            this.lblInput.Name = "lblInput";
            this.lblInput.Size = new System.Drawing.Size(34, 13);
            this.lblInput.TabIndex = 6;
            this.lblInput.Text = "Input:";
            // 
            // txtInput
            // 
            this.txtInput.Location = new System.Drawing.Point(25, 37);
            this.txtInput.Name = "txtInput";
            this.txtInput.Size = new System.Drawing.Size(616, 20);
            this.txtInput.TabIndex = 5;
            // 
            // FrmConfiguration
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(702, 323);
            this.Controls.Add(this.btnOK);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.tabMain);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "FrmConfiguration";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Configuration";
            this.tabMain.ResumeLayout(false);
            this.pageTranscoding.ResumeLayout(false);
            this.pageTranscoding.PerformLayout();
            this.grpPredefined.ResumeLayout(false);
            this.grpPredefined.PerformLayout();
            this.grpTranscoding.ResumeLayout(false);
            this.grpTranscoding.PerformLayout();
            this.pageTool.ResumeLayout(false);
            this.grpTTranscoding.ResumeLayout(false);
            this.grpTTranscoding.PerformLayout();
            this.grpTConversion.ResumeLayout(false);
            this.grpTConversion.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabMain;
        private System.Windows.Forms.TabPage pageTranscoding;
        private System.Windows.Forms.TabPage pageTool;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnOK;
        private System.Windows.Forms.TextBox txtWarning;
        private System.Windows.Forms.GroupBox grpPredefined;
        private System.Windows.Forms.GroupBox grpTranscoding;
        private System.Windows.Forms.TextBox txtTranscoding;
        private System.Windows.Forms.RadioButton rbtnAsf;
        private System.Windows.Forms.RadioButton rbtnMp4;
        private System.Windows.Forms.RadioButton rbtnCustom;
        private System.Windows.Forms.RadioButton rbtnWebm;
        private System.Windows.Forms.RadioButton rbtnTs;
        private System.Windows.Forms.GroupBox grpTTranscoding;
        private System.Windows.Forms.TextBox txtTTranscoding;
        private System.Windows.Forms.GroupBox grpTConversion;
        private System.Windows.Forms.Label lblOutput;
        private System.Windows.Forms.TextBox txtOutput;
        private System.Windows.Forms.ProgressBar progress;
        private System.Windows.Forms.Button btnBrowse;
        private System.Windows.Forms.Button btnConvert;
        private System.Windows.Forms.Timer timer;
        private System.Windows.Forms.Label lblInput;
        private System.Windows.Forms.TextBox txtInput;
    }
}