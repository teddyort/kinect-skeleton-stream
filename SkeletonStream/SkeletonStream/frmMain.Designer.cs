namespace SkeletonStream
{
    partial class frmMain
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
            this.lblStatus = new System.Windows.Forms.Label();
            this.dgvTable = new System.Windows.Forms.DataGridView();
            this.chkSeatedMode = new System.Windows.Forms.CheckBox();
            this.joint = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.orientation = new System.Windows.Forms.DataGridViewTextBoxColumn();
            ((System.ComponentModel.ISupportInitialize)(this.dgvTable)).BeginInit();
            this.SuspendLayout();
            // 
            // lblStatus
            // 
            this.lblStatus.AutoSize = true;
            this.lblStatus.Location = new System.Drawing.Point(9, 532);
            this.lblStatus.Name = "lblStatus";
            this.lblStatus.Size = new System.Drawing.Size(61, 13);
            this.lblStatus.TabIndex = 2;
            this.lblStatus.Text = "Initializing...";
            // 
            // dgvTable
            // 
            this.dgvTable.AllowUserToAddRows = false;
            this.dgvTable.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dgvTable.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvTable.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.joint,
            this.orientation});
            this.dgvTable.Location = new System.Drawing.Point(12, 12);
            this.dgvTable.Name = "dgvTable";
            this.dgvTable.Size = new System.Drawing.Size(508, 494);
            this.dgvTable.TabIndex = 3;
            // 
            // chkSeatedMode
            // 
            this.chkSeatedMode.AutoSize = true;
            this.chkSeatedMode.Checked = true;
            this.chkSeatedMode.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkSeatedMode.Location = new System.Drawing.Point(12, 512);
            this.chkSeatedMode.Name = "chkSeatedMode";
            this.chkSeatedMode.Size = new System.Drawing.Size(90, 17);
            this.chkSeatedMode.TabIndex = 4;
            this.chkSeatedMode.Text = "Seated Mode";
            this.chkSeatedMode.UseVisualStyleBackColor = true;
            this.chkSeatedMode.CheckedChanged += new System.EventHandler(this.chkSeatedMode_CheckedChanged);
            // 
            // joint
            // 
            this.joint.FillWeight = 76.14214F;
            this.joint.HeaderText = "Joint";
            this.joint.Name = "joint";
            // 
            // orientation
            // 
            this.orientation.FillWeight = 123.8579F;
            this.orientation.HeaderText = "Orientation";
            this.orientation.Name = "orientation";
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(532, 554);
            this.Controls.Add(this.chkSeatedMode);
            this.Controls.Add(this.dgvTable);
            this.Controls.Add(this.lblStatus);
            this.Name = "frmMain";
            this.Text = "Skeleton Stream";
            this.Load += new System.EventHandler(this.frmMain_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dgvTable)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblStatus;
        private System.Windows.Forms.DataGridView dgvTable;
        private System.Windows.Forms.CheckBox chkSeatedMode;
        private System.Windows.Forms.DataGridViewTextBoxColumn joint;
        private System.Windows.Forms.DataGridViewTextBoxColumn orientation;
    }
}

