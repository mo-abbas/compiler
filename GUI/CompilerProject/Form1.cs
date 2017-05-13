using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CompilerProject
{
    public partial class mainForm : Form
    {
        public const int WM_NCLBUTTONDOWN = 0xA1;
        public const int HT_CAPTION = 0x2;

        [DllImportAttribute("user32.dll")]
        public static extern int SendMessage(IntPtr hWnd, int Msg, int wParam, int lParam);
        [DllImportAttribute("user32.dll")]
        public static extern bool ReleaseCapture();
        public mainForm()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void codeToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void menuStrip1_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                ReleaseCapture();
                SendMessage(Handle, WM_NCLBUTTONDOWN, HT_CAPTION, 0);
            }
        }

        private void closeIcon_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void closeIcon_MouseHover(object sender, EventArgs e)
        {
           
        }

        private void closeIcon_MouseLeave(object sender, EventArgs e)
        {
            this.closeIcon.BackColor = System.Drawing.ColorTranslator.FromHtml("#d6dbe9");
        }

        private void closeIcon_MouseEnter(object sender, EventArgs e)
        {
            this.closeIcon.BackColor = System.Drawing.ColorTranslator.FromHtml("#bbbfca");
        }

        private void minBut_Click(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Minimized;
        }

        private void minBut_MouseEnter(object sender, EventArgs e)
        {
            this.minBut.BackColor = System.Drawing.ColorTranslator.FromHtml("#bbbfca");
        }

        private void minBut_MouseLeave(object sender, EventArgs e)
        {
            this.minBut.BackColor = System.Drawing.ColorTranslator.FromHtml("#d6dbe9");
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            codeEditor.Clear();
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            saveFileDialog1.ShowDialog();
        }

        private void saveFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            File.WriteAllText(saveFileDialog1.FileName, codeEditor.Text);
        }

        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            System.IO.StreamReader sr = new
                  System.IO.StreamReader(openFileDialog1.FileName);
            codeEditor.Text = sr.ReadToEnd();
        }
    }
}
