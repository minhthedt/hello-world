namespace GenerateSpecificationFile
{
    partial class Form1
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
            this.label1 = new System.Windows.Forms.Label();
            this.tbx_input = new System.Windows.Forms.TextBox();
            this.btn_open = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.tbx_outputName = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.tbx_category = new System.Windows.Forms.TextBox();
            this.btn_generate = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.tbx_outputDir = new System.Windows.Forms.TextBox();
            this.btn_set = new System.Windows.Forms.Button();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.settingToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.enable_open_outdir = new System.Windows.Forms.ToolStripMenuItem();
            this.enable_generate_outputname = new System.Windows.Forms.ToolStripMenuItem();
            this.menu_about = new System.Windows.Forms.ToolStripMenuItem();
            this.mn_enable_console = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(19, 72);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(70, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "InputFile (.tst)";
            // 
            // tbx_input
            // 
            this.tbx_input.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbx_input.Location = new System.Drawing.Point(118, 69);
            this.tbx_input.Name = "tbx_input";
            this.tbx_input.Size = new System.Drawing.Size(197, 20);
            this.tbx_input.TabIndex = 1;
            // 
            // btn_open
            // 
            this.btn_open.Location = new System.Drawing.Point(350, 67);
            this.btn_open.Name = "btn_open";
            this.btn_open.Size = new System.Drawing.Size(75, 23);
            this.btn_open.TabIndex = 2;
            this.btn_open.Text = "Open";
            this.btn_open.UseVisualStyleBackColor = true;
            this.btn_open.Click += new System.EventHandler(this.btn_open_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(19, 159);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(93, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "OutputName(.xlxs)";
            // 
            // tbx_outputName
            // 
            this.tbx_outputName.Location = new System.Drawing.Point(118, 156);
            this.tbx_outputName.Name = "tbx_outputName";
            this.tbx_outputName.Size = new System.Drawing.Size(197, 20);
            this.tbx_outputName.TabIndex = 4;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(19, 200);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(49, 13);
            this.label3.TabIndex = 5;
            this.label3.Text = "Category";
            // 
            // tbx_category
            // 
            this.tbx_category.Location = new System.Drawing.Point(118, 200);
            this.tbx_category.Name = "tbx_category";
            this.tbx_category.Size = new System.Drawing.Size(195, 20);
            this.tbx_category.TabIndex = 6;
            this.tbx_category.Text = "SWUP";
            // 
            // btn_generate
            // 
            this.btn_generate.Location = new System.Drawing.Point(118, 301);
            this.btn_generate.Name = "btn_generate";
            this.btn_generate.Size = new System.Drawing.Size(173, 52);
            this.btn_generate.TabIndex = 7;
            this.btn_generate.Text = "Generate";
            this.btn_generate.UseVisualStyleBackColor = true;
            this.btn_generate.Click += new System.EventHandler(this.btn_generate_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(19, 126);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(52, 13);
            this.label4.TabIndex = 8;
            this.label4.Text = "OutputDir";
            // 
            // tbx_outputDir
            // 
            this.tbx_outputDir.Location = new System.Drawing.Point(118, 119);
            this.tbx_outputDir.Name = "tbx_outputDir";
            this.tbx_outputDir.Size = new System.Drawing.Size(193, 20);
            this.tbx_outputDir.TabIndex = 9;
            // 
            // btn_set
            // 
            this.btn_set.Location = new System.Drawing.Point(350, 119);
            this.btn_set.Name = "btn_set";
            this.btn_set.Size = new System.Drawing.Size(75, 23);
            this.btn_set.TabIndex = 10;
            this.btn_set.Text = "...";
            this.btn_set.UseVisualStyleBackColor = true;
            this.btn_set.Click += new System.EventHandler(this.btn_set_Click);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.settingToolStripMenuItem,
            this.menu_about});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(449, 24);
            this.menuStrip1.TabIndex = 11;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // settingToolStripMenuItem
            // 
            this.settingToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.enable_open_outdir,
            this.enable_generate_outputname,
            this.mn_enable_console});
            this.settingToolStripMenuItem.Name = "settingToolStripMenuItem";
            this.settingToolStripMenuItem.Size = new System.Drawing.Size(55, 20);
            this.settingToolStripMenuItem.Text = "setting";
            // 
            // enable_open_outdir
            // 
            this.enable_open_outdir.Checked = true;
            this.enable_open_outdir.CheckState = System.Windows.Forms.CheckState.Checked;
            this.enable_open_outdir.Name = "enable_open_outdir";
            this.enable_open_outdir.Size = new System.Drawing.Size(249, 22);
            this.enable_open_outdir.Text = "auto open OputDir after finishing";
            this.enable_open_outdir.Click += new System.EventHandler(this.enable_open_outdir_Click);
            // 
            // enable_generate_outputname
            // 
            this.enable_generate_outputname.Checked = true;
            this.enable_generate_outputname.CheckState = System.Windows.Forms.CheckState.Checked;
            this.enable_generate_outputname.Name = "enable_generate_outputname";
            this.enable_generate_outputname.Size = new System.Drawing.Size(249, 22);
            this.enable_generate_outputname.Text = "auto generate outputName";
            this.enable_generate_outputname.Click += new System.EventHandler(this.enable_generate_outputname_Click);
            // 
            // menu_about
            // 
            this.menu_about.Name = "menu_about";
            this.menu_about.Size = new System.Drawing.Size(50, 20);
            this.menu_about.Text = "about";
            this.menu_about.Click += new System.EventHandler(this.menu_about_Click);
            // 
            // mn_enable_console
            // 
            this.mn_enable_console.Checked = true;
            this.mn_enable_console.CheckState = System.Windows.Forms.CheckState.Checked;
            this.mn_enable_console.Name = "mn_enable_console";
            this.mn_enable_console.Size = new System.Drawing.Size(249, 22);
            this.mn_enable_console.Text = "enable console log";
            this.mn_enable_console.Click += new System.EventHandler(this.mn_enable_console_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(449, 561);
            this.Controls.Add(this.btn_set);
            this.Controls.Add(this.tbx_outputDir);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.btn_generate);
            this.Controls.Add(this.tbx_category);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.tbx_outputName);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.btn_open);
            this.Controls.Add(this.tbx_input);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.menuStrip1);
            this.Name = "Form1";
            this.Text = "SpecTestGenerator_20190217";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox tbx_input;
        private System.Windows.Forms.Button btn_open;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox tbx_outputName;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox tbx_category;
        private System.Windows.Forms.Button btn_generate;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox tbx_outputDir;
        private System.Windows.Forms.Button btn_set;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem settingToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem enable_open_outdir;
        private System.Windows.Forms.ToolStripMenuItem menu_about;
        private System.Windows.Forms.ToolStripMenuItem enable_generate_outputname;
        private System.Windows.Forms.ToolStripMenuItem mn_enable_console;
    }
}

