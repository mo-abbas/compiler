namespace CompilerProject
{
    partial class mainForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(mainForm));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.codeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.buildToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.label1 = new System.Windows.Forms.Label();
            this.closeIcon = new System.Windows.Forms.PictureBox();
            this.progIcon = new System.Windows.Forms.PictureBox();
            this.minBut = new System.Windows.Forms.PictureBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.ErrorListRTB = new System.Windows.Forms.RichTextBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.SymbolTableGridView = new System.Windows.Forms.DataGridView();
            this.ColumnName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumnType = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumnScope = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumnConst = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.gbCodeEditor = new System.Windows.Forms.GroupBox();
            this.codeEditor = new FastColoredTextBoxNS.FastColoredTextBox();
            this.gBInterCode = new System.Windows.Forms.GroupBox();
            this.intCode = new FastColoredTextBoxNS.FastColoredTextBox();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.closeIcon)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.progIcon)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.minBut)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.SymbolTableGridView)).BeginInit();
            this.gbCodeEditor.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.codeEditor)).BeginInit();
            this.gBInterCode.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.intCode)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.AutoSize = false;
            this.menuStrip1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(214)))), ((int)(((byte)(219)))), ((int)(((byte)(233)))));
            this.menuStrip1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(41)))), ((int)(((byte)(57)))), ((int)(((byte)(85)))));
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.codeToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Padding = new System.Windows.Forms.Padding(6, 40, 0, 2);
            this.menuStrip1.Size = new System.Drawing.Size(1264, 65);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            this.menuStrip1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.menuStrip1_MouseDown);
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripMenuItem,
            this.openToolStripMenuItem,
            this.saveAsToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 23);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // newToolStripMenuItem
            // 
            this.newToolStripMenuItem.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(234)))), ((int)(((byte)(240)))), ((int)(((byte)(255)))));
            this.newToolStripMenuItem.Name = "newToolStripMenuItem";
            this.newToolStripMenuItem.Size = new System.Drawing.Size(114, 22);
            this.newToolStripMenuItem.Text = "New";
            this.newToolStripMenuItem.Click += new System.EventHandler(this.newToolStripMenuItem_Click);
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(234)))), ((int)(((byte)(240)))), ((int)(((byte)(255)))));
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.Size = new System.Drawing.Size(114, 22);
            this.openToolStripMenuItem.Text = "Open";
            this.openToolStripMenuItem.Click += new System.EventHandler(this.openToolStripMenuItem_Click);
            // 
            // saveAsToolStripMenuItem
            // 
            this.saveAsToolStripMenuItem.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(234)))), ((int)(((byte)(240)))), ((int)(((byte)(255)))));
            this.saveAsToolStripMenuItem.Name = "saveAsToolStripMenuItem";
            this.saveAsToolStripMenuItem.Size = new System.Drawing.Size(114, 22);
            this.saveAsToolStripMenuItem.Text = "Save As";
            this.saveAsToolStripMenuItem.Click += new System.EventHandler(this.saveAsToolStripMenuItem_Click);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(234)))), ((int)(((byte)(240)))), ((int)(((byte)(255)))));
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(114, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // codeToolStripMenuItem
            // 
            this.codeToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.buildToolStripMenuItem});
            this.codeToolStripMenuItem.Name = "codeToolStripMenuItem";
            this.codeToolStripMenuItem.Size = new System.Drawing.Size(47, 23);
            this.codeToolStripMenuItem.Text = "Code";
            // 
            // buildToolStripMenuItem
            // 
            this.buildToolStripMenuItem.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(234)))), ((int)(((byte)(240)))), ((int)(((byte)(255)))));
            this.buildToolStripMenuItem.Name = "buildToolStripMenuItem";
            this.buildToolStripMenuItem.Size = new System.Drawing.Size(101, 22);
            this.buildToolStripMenuItem.Text = "Build";
            this.buildToolStripMenuItem.Click += new System.EventHandler(this.buildToolStripMenuItem_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(214)))), ((int)(((byte)(219)))), ((int)(((byte)(233)))));
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(125)))), ((int)(((byte)(128)))));
            this.label1.Location = new System.Drawing.Point(42, 14);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(74, 16);
            this.label1.TabIndex = 1;
            this.label1.Text = "C Compiler";
            // 
            // closeIcon
            // 
            this.closeIcon.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(214)))), ((int)(((byte)(219)))), ((int)(((byte)(233)))));
            this.closeIcon.Image = global::CompilerProject.Properties.Resources.cancel2;
            this.closeIcon.Location = new System.Drawing.Point(1228, 0);
            this.closeIcon.Name = "closeIcon";
            this.closeIcon.Size = new System.Drawing.Size(36, 30);
            this.closeIcon.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.closeIcon.TabIndex = 3;
            this.closeIcon.TabStop = false;
            this.closeIcon.Click += new System.EventHandler(this.closeIcon_Click);
            this.closeIcon.MouseEnter += new System.EventHandler(this.closeIcon_MouseEnter);
            this.closeIcon.MouseLeave += new System.EventHandler(this.closeIcon_MouseLeave);
            // 
            // progIcon
            // 
            this.progIcon.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(214)))), ((int)(((byte)(219)))), ((int)(((byte)(233)))));
            this.progIcon.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.progIcon.Image = global::CompilerProject.Properties.Resources.meeting_point2;
            this.progIcon.Location = new System.Drawing.Point(12, 9);
            this.progIcon.Name = "progIcon";
            this.progIcon.Size = new System.Drawing.Size(24, 24);
            this.progIcon.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.progIcon.TabIndex = 2;
            this.progIcon.TabStop = false;
            // 
            // minBut
            // 
            this.minBut.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(214)))), ((int)(((byte)(219)))), ((int)(((byte)(233)))));
            this.minBut.Image = global::CompilerProject.Properties.Resources.minimize1;
            this.minBut.Location = new System.Drawing.Point(1192, 0);
            this.minBut.Name = "minBut";
            this.minBut.Size = new System.Drawing.Size(36, 30);
            this.minBut.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.minBut.TabIndex = 5;
            this.minBut.TabStop = false;
            this.minBut.Click += new System.EventHandler(this.minBut_Click);
            this.minBut.MouseEnter += new System.EventHandler(this.minBut_MouseEnter);
            this.minBut.MouseLeave += new System.EventHandler(this.minBut_MouseLeave);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.ErrorListRTB);
            this.groupBox1.Font = new System.Drawing.Font("Consolas", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox1.ForeColor = System.Drawing.Color.White;
            this.groupBox1.Location = new System.Drawing.Point(12, 554);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(960, 115);
            this.groupBox1.TabIndex = 7;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Error List";
            // 
            // ErrorListRTB
            // 
            this.ErrorListRTB.Location = new System.Drawing.Point(10, 19);
            this.ErrorListRTB.Name = "ErrorListRTB";
            this.ErrorListRTB.ReadOnly = true;
            this.ErrorListRTB.Size = new System.Drawing.Size(940, 84);
            this.ErrorListRTB.TabIndex = 0;
            this.ErrorListRTB.Text = "";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.SymbolTableGridView);
            this.groupBox2.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.groupBox2.Font = new System.Drawing.Font("Consolas", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox2.ForeColor = System.Drawing.Color.White;
            this.groupBox2.Location = new System.Drawing.Point(986, 83);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(266, 586);
            this.groupBox2.TabIndex = 8;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Variables";
            // 
            // SymbolTableGridView
            // 
            this.SymbolTableGridView.AllowUserToAddRows = false;
            this.SymbolTableGridView.AllowUserToDeleteRows = false;
            this.SymbolTableGridView.AllowUserToResizeColumns = false;
            this.SymbolTableGridView.AllowUserToResizeRows = false;
            this.SymbolTableGridView.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.SymbolTableGridView.BackgroundColor = System.Drawing.Color.FromArgb(((int)(((byte)(230)))), ((int)(((byte)(231)))), ((int)(((byte)(232)))));
            this.SymbolTableGridView.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.SymbolTableGridView.ClipboardCopyMode = System.Windows.Forms.DataGridViewClipboardCopyMode.Disable;
            this.SymbolTableGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.SymbolTableGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.ColumnName,
            this.ColumnType,
            this.ColumnScope,
            this.ColumnConst});
            this.SymbolTableGridView.EditMode = System.Windows.Forms.DataGridViewEditMode.EditProgrammatically;
            this.SymbolTableGridView.Location = new System.Drawing.Point(6, 19);
            this.SymbolTableGridView.Name = "SymbolTableGridView";
            this.SymbolTableGridView.ReadOnly = true;
            this.SymbolTableGridView.RowHeadersVisible = false;
            this.SymbolTableGridView.RowHeadersWidthSizeMode = System.Windows.Forms.DataGridViewRowHeadersWidthSizeMode.AutoSizeToAllHeaders;
            this.SymbolTableGridView.Size = new System.Drawing.Size(254, 558);
            this.SymbolTableGridView.TabIndex = 0;
            // 
            // ColumnName
            // 
            this.ColumnName.HeaderText = "Name";
            this.ColumnName.Name = "ColumnName";
            this.ColumnName.ReadOnly = true;
            this.ColumnName.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            // 
            // ColumnType
            // 
            this.ColumnType.HeaderText = "Type";
            this.ColumnType.Name = "ColumnType";
            this.ColumnType.ReadOnly = true;
            this.ColumnType.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            // 
            // ColumnScope
            // 
            this.ColumnScope.HeaderText = "Scope";
            this.ColumnScope.Name = "ColumnScope";
            this.ColumnScope.ReadOnly = true;
            this.ColumnScope.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            // 
            // ColumnConst
            // 
            this.ColumnConst.HeaderText = "Constant";
            this.ColumnConst.Name = "ColumnConst";
            this.ColumnConst.ReadOnly = true;
            this.ColumnConst.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.Filter = "C files |*.c";
            this.openFileDialog1.FileOk += new System.ComponentModel.CancelEventHandler(this.openFileDialog1_FileOk);
            // 
            // saveFileDialog1
            // 
            this.saveFileDialog1.Filter = "C files|*.c";
            this.saveFileDialog1.Title = "Save code file";
            this.saveFileDialog1.FileOk += new System.ComponentModel.CancelEventHandler(this.saveFileDialog1_FileOk);
            // 
            // gbCodeEditor
            // 
            this.gbCodeEditor.Controls.Add(this.codeEditor);
            this.gbCodeEditor.ForeColor = System.Drawing.Color.White;
            this.gbCodeEditor.Location = new System.Drawing.Point(12, 83);
            this.gbCodeEditor.Name = "gbCodeEditor";
            this.gbCodeEditor.Size = new System.Drawing.Size(563, 465);
            this.gbCodeEditor.TabIndex = 9;
            this.gbCodeEditor.TabStop = false;
            this.gbCodeEditor.Text = "Code Editor";
            // 
            // codeEditor
            // 
            this.codeEditor.AutoCompleteBrackets = true;
            this.codeEditor.AutoCompleteBracketsList = new char[] {
        '(',
        ')',
        '{',
        '}',
        '[',
        ']',
        '\"',
        '\"',
        '\'',
        '\''};
            this.codeEditor.AutoIndentCharsPatterns = "\r\n^\\s*[\\w\\.]+(\\s\\w+)?\\s*(?<range>=)\\s*(?<range>[^;]+);\r\n^\\s*(case|default)\\s*[^:]" +
    "*(?<range>:)\\s*(?<range>[^;]+);\r\n";
            this.codeEditor.AutoScrollMinSize = new System.Drawing.Size(25, 15);
            this.codeEditor.BackBrush = null;
            this.codeEditor.BracketsHighlightStrategy = FastColoredTextBoxNS.BracketsHighlightStrategy.Strategy2;
            this.codeEditor.CharHeight = 15;
            this.codeEditor.CharWidth = 7;
            this.codeEditor.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.codeEditor.DisabledColor = System.Drawing.Color.FromArgb(((int)(((byte)(100)))), ((int)(((byte)(180)))), ((int)(((byte)(180)))), ((int)(((byte)(180)))));
            this.codeEditor.Font = new System.Drawing.Font("Consolas", 9.75F);
            this.codeEditor.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.codeEditor.IsReplaceMode = false;
            this.codeEditor.Language = FastColoredTextBoxNS.Language.CSharp;
            this.codeEditor.LeftBracket = '(';
            this.codeEditor.LeftBracket2 = '{';
            this.codeEditor.Location = new System.Drawing.Point(10, 19);
            this.codeEditor.Name = "codeEditor";
            this.codeEditor.Paddings = new System.Windows.Forms.Padding(0);
            this.codeEditor.RightBracket = ')';
            this.codeEditor.RightBracket2 = '}';
            this.codeEditor.SelectionColor = System.Drawing.Color.FromArgb(((int)(((byte)(60)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))), ((int)(((byte)(255)))));
            this.codeEditor.ServiceColors = ((FastColoredTextBoxNS.ServiceColors)(resources.GetObject("codeEditor.ServiceColors")));
            this.codeEditor.Size = new System.Drawing.Size(547, 440);
            this.codeEditor.TabIndex = 0;
            this.codeEditor.Zoom = 100;
            // 
            // gBInterCode
            // 
            this.gBInterCode.Controls.Add(this.intCode);
            this.gBInterCode.ForeColor = System.Drawing.Color.White;
            this.gBInterCode.Location = new System.Drawing.Point(581, 83);
            this.gBInterCode.Name = "gBInterCode";
            this.gBInterCode.Size = new System.Drawing.Size(391, 465);
            this.gBInterCode.TabIndex = 10;
            this.gBInterCode.TabStop = false;
            this.gBInterCode.Text = "Intermediate Code";
            // 
            // intCode
            // 
            this.intCode.AutoCompleteBracketsList = new char[] {
        '(',
        ')',
        '{',
        '}',
        '[',
        ']',
        '\"',
        '\"',
        '\'',
        '\''};
            this.intCode.AutoIndentCharsPatterns = "\r\n^\\s*\\$[\\w\\.\\[\\]\\\'\\\"]+\\s*(?<range>=)\\s*(?<range>[^;]+);\r\n";
            this.intCode.AutoScrollMinSize = new System.Drawing.Size(25, 15);
            this.intCode.BackBrush = null;
            this.intCode.BracketsHighlightStrategy = FastColoredTextBoxNS.BracketsHighlightStrategy.Strategy2;
            this.intCode.CharHeight = 15;
            this.intCode.CharWidth = 7;
            this.intCode.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.intCode.DisabledColor = System.Drawing.Color.FromArgb(((int)(((byte)(100)))), ((int)(((byte)(180)))), ((int)(((byte)(180)))), ((int)(((byte)(180)))));
            this.intCode.Font = new System.Drawing.Font("Consolas", 9.75F);
            this.intCode.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.intCode.IsReplaceMode = false;
            this.intCode.Language = FastColoredTextBoxNS.Language.PHP;
            this.intCode.LeftBracket = '(';
            this.intCode.LeftBracket2 = '{';
            this.intCode.Location = new System.Drawing.Point(10, 19);
            this.intCode.Name = "intCode";
            this.intCode.Paddings = new System.Windows.Forms.Padding(0);
            this.intCode.ReadOnly = true;
            this.intCode.RightBracket = ')';
            this.intCode.RightBracket2 = '}';
            this.intCode.SelectionColor = System.Drawing.Color.FromArgb(((int)(((byte)(60)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))), ((int)(((byte)(255)))));
            this.intCode.ServiceColors = ((FastColoredTextBoxNS.ServiceColors)(resources.GetObject("intCode.ServiceColors")));
            this.intCode.Size = new System.Drawing.Size(375, 440);
            this.intCode.TabIndex = 0;
            this.intCode.Zoom = 100;
            // 
            // mainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(41)))), ((int)(((byte)(58)))), ((int)(((byte)(86)))));
            this.ClientSize = new System.Drawing.Size(1264, 681);
            this.Controls.Add(this.gBInterCode);
            this.Controls.Add(this.gbCodeEditor);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.minBut);
            this.Controls.Add(this.closeIcon);
            this.Controls.Add(this.progIcon);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "mainForm";
            this.Text = "C Compiler";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.closeIcon)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.progIcon)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.minBut)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.SymbolTableGridView)).EndInit();
            this.gbCodeEditor.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.codeEditor)).EndInit();
            this.gBInterCode.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.intCode)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveAsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem codeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem buildToolStripMenuItem;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.PictureBox progIcon;
        private System.Windows.Forms.PictureBox closeIcon;
        private System.Windows.Forms.PictureBox minBut;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RichTextBox ErrorListRTB;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.DataGridView SymbolTableGridView;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnConst;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnScope;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnType;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnName;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.GroupBox gbCodeEditor;
        private System.Windows.Forms.GroupBox gBInterCode;
        private FastColoredTextBoxNS.FastColoredTextBox intCode;
        private FastColoredTextBoxNS.FastColoredTextBox codeEditor;
    }
}

