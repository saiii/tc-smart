namespace CsServer
{
    partial class frmShutdown
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
            this.pgStatus = new System.Windows.Forms.ProgressBar();
            this.SuspendLayout();
            // 
            // pgStatus
            // 
            this.pgStatus.Location = new System.Drawing.Point(5, 22);
            this.pgStatus.Name = "pgStatus";
            this.pgStatus.Size = new System.Drawing.Size(339, 13);
            this.pgStatus.TabIndex = 1;
            // 
            // frmShutdown
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(351, 43);
            this.Controls.Add(this.pgStatus);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "frmShutdown";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Shutdown... Please wait";
            this.Load += new System.EventHandler(this.frmShutdown_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ProgressBar pgStatus;

    }
}