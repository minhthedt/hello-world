using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace GenerateSpecificationFile
{
   struct Form1Data
    {
        public string inpuFilePath;
        public string outputDir;
        public string outputName;
        public string category;
        public bool auto_open_outputDir;
        public bool auto_generate_outputName;
        public bool enable_console;
    };

    public partial class Form1 : Form
    {

        public Form1()
        {
            InitializeComponent();

            this.tbx_outputDir.Text = Path.GetDirectoryName(Application.ExecutablePath);
            if(enable_generate_outputname.Checked)
            {
                this.tbx_outputName.Enabled = false;
            }
        }

        public void updateOutputName(string str)
        {
            this.tbx_outputName.Text = str;
        }

        private void btn_open_Click(object sender, EventArgs e)
        {
            OpenFileDialog diag = new OpenFileDialog();
            diag.Title = "Open Test Case File";
            diag.Filter = "txt files (*.tst)|*.tst|All files (*.*)|*.*";
            diag.RestoreDirectory = true;
            if (diag.ShowDialog() == DialogResult.OK)
            {
                tbx_input.Text = diag.FileName;
                //auto create output filename
                if(enable_generate_outputname.Checked == false)
                {
                    string fileNane = Path.GetFileName(tbx_input.Text);
                    string extension = System.IO.Path.GetExtension(fileNane);
                    string name = fileNane.Substring(0, fileNane.Length - extension.Length);
                    //update outputName
                    tbx_outputName.Text = "Specification_" + name + ".xlsx";
                }

            }
        }

        private void btn_generate_Click(object sender, EventArgs e)
        {
            Form1Data dt = new Form1Data();
            dt.inpuFilePath = tbx_input.Text;
            dt.outputDir = tbx_outputDir.Text;
            dt.outputName = tbx_outputName.Text;
            dt.category = tbx_category.Text;
            dt.auto_open_outputDir = enable_open_outdir.Checked;
            dt.auto_generate_outputName = enable_generate_outputname.Checked;
            dt.enable_console = mn_enable_console.Checked;

            Form1Handle.GenerateXlxsFile(dt, this);
        }


        private void btn_set_Click(object sender, EventArgs e)
        {
            // Show the FolderBrowserDialog.
            FolderBrowserDialog diag = new System.Windows.Forms.FolderBrowserDialog();
            diag.SelectedPath = tbx_outputDir.Text;
            if (diag.ShowDialog() == DialogResult.OK)
            {
                tbx_outputDir.Text = diag.SelectedPath;
            }
        }

        private void enable_open_outdir_Click(object sender, EventArgs e)
        {
            enable_open_outdir.Checked = !enable_open_outdir.Checked;
        }

        private void enable_generate_outputname_Click(object sender, EventArgs e)
        {
            enable_generate_outputname.Checked = !enable_generate_outputname.Checked;
            if(enable_generate_outputname.Checked)
            {
                this.tbx_outputName.Text = "";
                this.tbx_outputName.Enabled = false;
            }
            else
            {
                this.tbx_outputName.Enabled = true;
                if (String.IsNullOrEmpty(tbx_input.Text))
                {
                    string fileNane = Path.GetFileName(tbx_input.Text);
                    string extension = System.IO.Path.GetExtension(fileNane);
                    string name = fileNane.Substring(0, fileNane.Length - extension.Length);
                    //update outputName
                    tbx_outputName.Text = "Specification_" + name + ".xlsx";
                }

            }
        }

        private void menu_about_Click(object sender, EventArgs e)
        {
            System.Windows.Forms.MessageBox.Show("Copyright of LG DCV Electronics Inc. \n" +
                "\nContact: " +
                "\n  hung.nguyenduc@lge.com" +
                "\n  the.vu@lge.com\n" +
                "\nVersion 2019.02.27\n" +
                "    + Fix : Missed reading note of field (_VERIFY,_PRECOND,...) when it was texted more than one line\n" 
                );
        }

        private void mn_enable_console_Click(object sender, EventArgs e)
        {
            //mn_enable_console.Checked = !mn_enable_console.Checked;
        }
    }
}
