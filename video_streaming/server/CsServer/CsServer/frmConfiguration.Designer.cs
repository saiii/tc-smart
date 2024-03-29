﻿namespace CsServer
{
    partial class frmConfiguration
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmConfiguration));
            this.flpMain = new System.Windows.Forms.FlowLayoutPanel();
            this.lblTranscode = new System.Windows.Forms.Label();
            this.txtTranscode = new System.Windows.Forms.TextBox();
            this.btnApply = new System.Windows.Forms.Button();
            this.txtWarning = new System.Windows.Forms.TextBox();
            this.flpIP = new System.Windows.Forms.FlowLayoutPanel();
            this.lblIP = new System.Windows.Forms.Label();
            this.lstIP = new System.Windows.Forms.ListBox();
            this.flpMain.SuspendLayout();
            this.flpIP.SuspendLayout();
            this.SuspendLayout();
            // 
            // flpMain
            // 
            this.flpMain.Controls.Add(this.lblTranscode);
            this.flpMain.Controls.Add(this.txtTranscode);
            this.flpMain.Location = new System.Drawing.Point(3, 124);
            this.flpMain.Name = "flpMain";
            this.flpMain.Size = new System.Drawing.Size(393, 29);
            this.flpMain.TabIndex = 1;
            // 
            // lblTranscode
            // 
            this.lblTranscode.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.lblTranscode.AutoSize = true;
            this.lblTranscode.Location = new System.Drawing.Point(3, 6);
            this.lblTranscode.Name = "lblTranscode";
            this.lblTranscode.Size = new System.Drawing.Size(58, 13);
            this.lblTranscode.TabIndex = 0;
            this.lblTranscode.Text = "Transcode";
            // 
            // txtTranscode
            // 
            this.txtTranscode.Location = new System.Drawing.Point(67, 3);
            this.txtTranscode.Name = "txtTranscode";
            this.txtTranscode.Size = new System.Drawing.Size(320, 20);
            this.txtTranscode.TabIndex = 1;
            // 
            // btnApply
            // 
            this.btnApply.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnApply.Location = new System.Drawing.Point(321, 218);
            this.btnApply.Name = "btnApply";
            this.btnApply.Size = new System.Drawing.Size(75, 20);
            this.btnApply.TabIndex = 2;
            this.btnApply.Text = "Apply";
            this.btnApply.UseVisualStyleBackColor = true;
            this.btnApply.Click += new System.EventHandler(this.btnApply_Click);
            // 
            // txtWarning
            // 
            this.txtWarning.Location = new System.Drawing.Point(3, 1);
            this.txtWarning.Multiline = true;
            this.txtWarning.Name = "txtWarning";
            this.txtWarning.ReadOnly = true;
            this.txtWarning.Size = new System.Drawing.Size(393, 117);
            this.txtWarning.TabIndex = 2;
            this.txtWarning.Text = resources.GetString("txtWarning.Text");
            // 
            // flpIP
            // 
            this.flpIP.Controls.Add(this.lblIP);
            this.flpIP.Controls.Add(this.lstIP);
            this.flpIP.Location = new System.Drawing.Point(3, 159);
            this.flpIP.Name = "flpIP";
            this.flpIP.Size = new System.Drawing.Size(393, 53);
            this.flpIP.TabIndex = 3;
            // 
            // lblIP
            // 
            this.lblIP.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.lblIP.Location = new System.Drawing.Point(3, 13);
            this.lblIP.Name = "lblIP";
            this.lblIP.Size = new System.Drawing.Size(58, 23);
            this.lblIP.TabIndex = 0;
            this.lblIP.Text = "IP";
            this.lblIP.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lstIP
            // 
            this.lstIP.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.lstIP.FormattingEnabled = true;
            this.lstIP.Location = new System.Drawing.Point(67, 3);
            this.lstIP.Name = "lstIP";
            this.lstIP.Size = new System.Drawing.Size(320, 43);
            this.lstIP.TabIndex = 1;
            // 
            // frmConfiguration
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(402, 242);
            this.Controls.Add(this.flpIP);
            this.Controls.Add(this.txtWarning);
            this.Controls.Add(this.btnApply);
            this.Controls.Add(this.flpMain);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "frmConfiguration";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Configuration";
            this.Load += new System.EventHandler(this.frmConfiguration_Load);
            this.flpMain.ResumeLayout(false);
            this.flpMain.PerformLayout();
            this.flpIP.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.FlowLayoutPanel flpMain;
        private System.Windows.Forms.Label lblTranscode;
        private System.Windows.Forms.TextBox txtTranscode;
        private System.Windows.Forms.Button btnApply;
        private System.Windows.Forms.TextBox txtWarning;
        private System.Windows.Forms.FlowLayoutPanel flpIP;
        private System.Windows.Forms.Label lblIP;
        private System.Windows.Forms.ListBox lstIP;
    }
}