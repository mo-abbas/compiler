using FileHelpers;
using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Text.RegularExpressions;
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

        private void buildToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ErrorListRTB.Text = "";
            SymbolTableGridView.Rows.Clear();

            string inputFile = Path.GetTempFileName();
            string outFile = Path.GetTempFileName();
            string SymbolFile = Path.GetTempFileName();
            string errorFile = Path.GetTempFileName();
            string WarnFile = Path.GetTempFileName();

            File.WriteAllText(inputFile, codeEditor.Text);
            runCompiler(outFile, errorFile, WarnFile, SymbolFile, inputFile);
            changeTbTextfromFile(intCode, outFile);
            UpdateErrorList(errorFile, WarnFile);
            UpdateSymbolTableGrid(SymbolFile);

            File.Delete(inputFile);
            File.Delete(outFile);
            File.Delete(SymbolFile);
            File.Delete(errorFile);
            File.Delete(WarnFile);
        }
        private void runCompiler(string outFile, string errorFile, string WarnFile, string SymbolFile, string inputFile)
        {
            var process = new Process();
            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.FileName = "cmd.exe";
            startInfo.Arguments = "/C Compilers.exe \"" + outFile + "\" \"" + errorFile + "\" \"" + WarnFile + "\" \"" + SymbolFile + "\" < \"" + inputFile + "\"";
            startInfo.WindowStyle = ProcessWindowStyle.Hidden;
            process.StartInfo = startInfo;
            process.Start();
            process.WaitForExit(int.MaxValue);
         }

        private void changeTbTextfromFile(TextBox Tb, String file)
        {
            Tb.Text = File.ReadAllText(file);
        }
        private void changeTbTextfromFile(FastColoredTextBoxNS.FastColoredTextBox Tb, String file)
        {
            Tb.Text = File.ReadAllText(file);
        }
        private void UpdateErrorList(string errorFile, string WarnFile)
        {
            string[] errors = File.ReadAllLines(errorFile);
            string[] warnings = File.ReadAllLines(WarnFile);
            SortedList<int,string> errorsSL = new SortedList<int,string>();
            foreach (string line in errors)
            {
                string[] words = line.Split(' ');
                int lineNum = int.Parse(words[2].Substring(0, words[2].Length - 1));
                errorsSL.Add(lineNum,line);
            }


            SortedList<int, string> warningsSL = new SortedList<int, string>();
            foreach (string line in warnings)
            {
                string[] words = line.Split(' ');
                int lineNum = int.Parse(words[2].Substring(0, words[2].Length - 1));
                warningsSL.Add(lineNum, line);
            }
            foreach (KeyValuePair<int,string> line in errorsSL)
            {

                ErrorListRTB.Text += " "+line.Value+"\n";
            }
            foreach (KeyValuePair<int,string> line in warningsSL)
            {
                ErrorListRTB.Text += " " + line.Value + "\n";
            }

            Regex regExp = new Regex(
                    @"\b(ERROR|WARNING)\b");

            foreach (Match match in regExp.Matches(ErrorListRTB.Text))
            {
                ErrorListRTB.Select(match.Index, match.Length);
                if (match.Value == "ERROR")
                    ErrorListRTB.SelectionColor = Color.Red;
                else
                    ErrorListRTB.SelectionColor = Color.DarkGoldenrod;
            }
        }
        private void UpdateSymbolTableGrid(string SymbolTable)
        {
            var engine = new FileHelperEngine<delimitedFile>();
            var records = engine.ReadFile(SymbolTable);
            for (int i = 1; i < records.Length; i++)
            {
                SymbolTableGridView.Rows.Add(records[i].Name, records[i].Type, records[i].ScopeId, records[i].Constant);
            }
            SymbolTableGridView.ForeColor = Color.Black;
        }

    }

    [DelimitedRecord(",")]
    class delimitedFile
    {
        public string Name;
        public string Type;
        public string ScopeId;
        public string Constant;
    }
}
