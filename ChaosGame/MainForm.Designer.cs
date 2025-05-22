namespace ChaosGame
{
    partial class MainForm
    {
        private System.ComponentModel.IContainer components = null;

        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        private void InitializeComponent()
        {
            pictureBox = new PictureBox();
            btnRun = new Button();
            txtQ = new TextBox();
            label1 = new Label();
            txtIterations = new TextBox();
            label2 = new Label();
            btnSave = new Button();
            groupBox1 = new GroupBox();
            btnSetVertices = new Button();
            label9 = new Label();
            txtDY = new TextBox();
            txtDX = new TextBox();
            label7 = new Label();
            txtCY = new TextBox();
            txtCX = new TextBox();
            label5 = new Label();
            txtBY = new TextBox();
            txtBX = new TextBox();
            label3 = new Label();
            txtAY = new TextBox();
            txtAX = new TextBox();
            groupBox2 = new GroupBox();
            btnSetX0 = new Button();
            label12 = new Label();
            label11 = new Label();
            txtX0Y = new TextBox();
            txtX0X = new TextBox();
            groupBox3 = new GroupBox();
            btnReset = new Button();
            btnMoveDown = new Button();
            btnMoveUp = new Button();
            btnMoveRight = new Button();
            btnMoveLeft = new Button();
            btnZoomOut = new Button();
            btnZoomIn = new Button();
            label13 = new Label();
            txtZ = new TextBox();
            label4 = new Label();
            label6 = new Label();
            label8 = new Label();
            label10 = new Label();
            label14 = new Label();
            label15 = new Label();
            label16 = new Label();
            label17 = new Label();
            ((System.ComponentModel.ISupportInitialize)pictureBox).BeginInit();
            groupBox1.SuspendLayout();
            groupBox2.SuspendLayout();
            groupBox3.SuspendLayout();
            SuspendLayout();

            pictureBox.Location = new Point(14, 14);
            pictureBox.Margin = new Padding(4, 3, 4, 3);
            pictureBox.Name = "pictureBox";
            pictureBox.Size = new Size(700, 692);
            pictureBox.TabIndex = 0;
            pictureBox.TabStop = false;

            btnRun.Location = new Point(721, 14);
            btnRun.Margin = new Padding(4, 3, 4, 3);
            btnRun.Name = "btnRun";
            btnRun.Size = new Size(198, 27);
            btnRun.TabIndex = 1;
            btnRun.Text = "Запустить игру";
            btnRun.UseVisualStyleBackColor = true;
            btnRun.Click += btnRun_Click;

            // q
            txtQ.Location = new Point(758, 47);
            txtQ.Margin = new Padding(4, 3, 4, 3);
            txtQ.Name = "txtQ";
            txtQ.Size = new Size(116, 23);
            txtQ.TabIndex = 2;
            txtQ.Text = "0.5";

            label1.AutoSize = true;
            label1.Location = new Point(721, 51);
            label1.Margin = new Padding(4, 0, 4, 0);
            label1.Name = "label1";
            label1.Size = new Size(28, 15);
            label1.TabIndex = 3;
            label1.Text = "q = ";

            //iter 
            txtIterations.Location = new Point(758, 77);
            txtIterations.Margin = new Padding(4, 3, 4, 3);
            txtIterations.Name = "txtIterations";
            txtIterations.Size = new Size(116, 23);
            txtIterations.TabIndex = 4;
            txtIterations.Text = "100000";

            label2.AutoSize = true;
            label2.Location = new Point(721, 81);
            label2.Margin = new Padding(4, 0, 4, 0);
            label2.Name = "label2";
            label2.Size = new Size(28, 15);
            label2.TabIndex = 5;
            label2.Text = "n = ";
 
            //save
            btnSave.Location = new Point(721, 107);
            btnSave.Margin = new Padding(4, 3, 4, 3);
            btnSave.Name = "btnSave";
            btnSave.Size = new Size(198, 27);
            btnSave.TabIndex = 6;
            btnSave.Text = "Сохранить изображение";
            btnSave.UseVisualStyleBackColor = true;
            btnSave.Click += btnSave_Click;

 
            groupBox1.Controls.Add(label17);
            groupBox1.Controls.Add(label16);
            groupBox1.Controls.Add(label15);
            groupBox1.Controls.Add(label14);
            groupBox1.Controls.Add(label10);
            groupBox1.Controls.Add(label8);
            groupBox1.Controls.Add(label6);
            groupBox1.Controls.Add(label4);
            groupBox1.Controls.Add(btnSetVertices);
            groupBox1.Controls.Add(label9);
            groupBox1.Controls.Add(txtDY);
            groupBox1.Controls.Add(txtDX);
            groupBox1.Controls.Add(label7);
            groupBox1.Controls.Add(txtCY);
            groupBox1.Controls.Add(txtCX);
            groupBox1.Controls.Add(label5);
            groupBox1.Controls.Add(txtBY);
            groupBox1.Controls.Add(txtBX);
            groupBox1.Controls.Add(label3);
            groupBox1.Controls.Add(txtAY);
            groupBox1.Controls.Add(txtAX);
            groupBox1.Location = new Point(721, 141);
            groupBox1.Margin = new Padding(4, 3, 4, 3);
            groupBox1.Name = "groupBox1";
            groupBox1.Padding = new Padding(4, 3, 4, 3);
            groupBox1.Size = new Size(198, 231);
            groupBox1.TabIndex = 7;
            groupBox1.TabStop = false;
            groupBox1.Text = "Вершины";

            btnSetVertices.Location = new Point(7, 138);
            btnSetVertices.Margin = new Padding(4, 3, 4, 3);
            btnSetVertices.Name = "btnSetVertices";
            btnSetVertices.Size = new Size(180, 27);
            btnSetVertices.TabIndex = 16;
            btnSetVertices.Text = "Установить вершины";
            btnSetVertices.UseVisualStyleBackColor = true;
            btnSetVertices.Click += btnSetVertices_Click;

            label9.AutoSize = true;
            label9.Location = new Point(7, 112);
            label9.Margin = new Padding(4, 0, 4, 0);
            label9.Name = "label9";
            label9.Size = new Size(15, 15);
            label9.TabIndex = 14;
            label9.Text = "D";


            txtDY.Location = new Point(140, 108);
            txtDY.Margin = new Padding(4, 3, 4, 3);
            txtDY.Name = "txtDY";
            txtDY.Size = new Size(46, 23);
            txtDY.TabIndex = 13;
            txtDY.Text = "1";
 
            txtDX.Location = new Point(70, 108);
            txtDX.Margin = new Padding(4, 3, 4, 3);
            txtDX.Name = "txtDX";
            txtDX.Size = new Size(46, 23);
            txtDX.TabIndex = 12;
            txtDX.Text = "0";

            label7.AutoSize = true;
            label7.Location = new Point(7, 82);
            label7.Margin = new Padding(4, 0, 4, 0);
            label7.Name = "label7";
            label7.Size = new Size(15, 15);
            label7.TabIndex = 10;
            label7.Text = "C";


            txtCY.Location = new Point(140, 78);
            txtCY.Margin = new Padding(4, 3, 4, 3);
            txtCY.Name = "txtCY";
            txtCY.Size = new Size(46, 23);
            txtCY.TabIndex = 9;
            txtCY.Text = "1";
 
            txtCX.Location = new Point(70, 78);
            txtCX.Margin = new Padding(4, 3, 4, 3);
            txtCX.Name = "txtCX";
            txtCX.Size = new Size(46, 23);
            txtCX.TabIndex = 8;
            txtCX.Text = "1";

            label5.AutoSize = true;
            label5.Location = new Point(7, 52);
            label5.Margin = new Padding(4, 0, 4, 0);
            label5.Name = "label5";
            label5.Size = new Size(14, 15);
            label5.TabIndex = 6;
            label5.Text = "B";

            txtBY.Location = new Point(140, 48);
            txtBY.Margin = new Padding(4, 3, 4, 3);
            txtBY.Name = "txtBY";
            txtBY.Size = new Size(46, 23);
            txtBY.TabIndex = 5;
            txtBY.Text = "0";

            txtBX.Location = new Point(70, 48);
            txtBX.Margin = new Padding(4, 3, 4, 3);
            txtBX.Name = "txtBX";
            txtBX.Size = new Size(46, 23);
            txtBX.TabIndex = 4;
            txtBX.Text = "1";

            label3.AutoSize = true;
            label3.Location = new Point(7, 22);
            label3.Margin = new Padding(4, 0, 4, 0);
            label3.Name = "label3";
            label3.Size = new Size(15, 15);
            label3.TabIndex = 2;
            label3.Text = "A";

            txtAY.Location = new Point(140, 18);
            txtAY.Margin = new Padding(4, 3, 4, 3);
            txtAY.Name = "txtAY";
            txtAY.Size = new Size(46, 23);
            txtAY.TabIndex = 1;
            txtAY.Text = "0";

            txtAX.Location = new Point(70, 18);
            txtAX.Margin = new Padding(4, 3, 4, 3);
            txtAX.Name = "txtAX";
            txtAX.Size = new Size(46, 23);
            txtAX.TabIndex = 0;
            txtAX.Text = "0";

            groupBox2.Controls.Add(btnSetX0);
            groupBox2.Controls.Add(label12);
            groupBox2.Controls.Add(label11);
            groupBox2.Controls.Add(txtX0Y);
            groupBox2.Controls.Add(txtX0X);
            groupBox2.Location = new Point(721, 378);
            groupBox2.Margin = new Padding(4, 3, 4, 3);
            groupBox2.Name = "groupBox2";
            groupBox2.Padding = new Padding(4, 3, 4, 3);
            groupBox2.Size = new Size(198, 115);
            groupBox2.TabIndex = 8;
            groupBox2.TabStop = false;
            groupBox2.Text = "Начальная точка X0";
            
            // x0
            btnSetX0.Location = new Point(7, 52);
            btnSetX0.Margin = new Padding(4, 3, 4, 3);
            btnSetX0.Name = "btnSetX0";
            btnSetX0.Size = new Size(180, 27);
            btnSetX0.TabIndex = 4;
            btnSetX0.Text = "Установить X0";
            btnSetX0.UseVisualStyleBackColor = true;
            btnSetX0.Click += btnSetX0_Click;

            label12.AutoSize = true;
            label12.Location = new Point(124, 25);
            label12.Margin = new Padding(4, 0, 4, 0);
            label12.Name = "label12";
            label12.Size = new Size(14, 15);
            label12.TabIndex = 3;
            label12.Text = "Y";

            label11.AutoSize = true;
            label11.Location = new Point(48, 25);
            label11.Margin = new Padding(4, 0, 4, 0);
            label11.Name = "label11";
            label11.Size = new Size(14, 15);
            label11.TabIndex = 2;
            label11.Text = "X";

            txtX0Y.Location = new Point(140, 22);
            txtX0Y.Margin = new Padding(4, 3, 4, 3);
            txtX0Y.Name = "txtX0Y";
            txtX0Y.Size = new Size(46, 23);
            txtX0Y.TabIndex = 1;
            txtX0Y.Text = "0.5";

            txtX0X.Location = new Point(70, 22);
            txtX0X.Margin = new Padding(4, 3, 4, 3);
            txtX0X.Name = "txtX0X";
            txtX0X.Size = new Size(46, 23);
            txtX0X.TabIndex = 0;
            txtX0X.Text = "0.5";

            groupBox3.Controls.Add(btnReset);
            groupBox3.Controls.Add(btnMoveDown);
            groupBox3.Controls.Add(btnMoveUp);
            groupBox3.Controls.Add(btnMoveRight);
            groupBox3.Controls.Add(btnMoveLeft);
            groupBox3.Controls.Add(btnZoomOut);
            groupBox3.Controls.Add(btnZoomIn);
            groupBox3.Location = new Point(721, 501);
            groupBox3.Margin = new Padding(4, 3, 4, 3);
            groupBox3.Name = "groupBox3";
            groupBox3.Padding = new Padding(4, 3, 4, 3);
            groupBox3.Size = new Size(198, 205);
            groupBox3.TabIndex = 9;
            groupBox3.TabStop = false;
            groupBox3.Text = "Управление видом";

            //reset
            btnReset.Location = new Point(7, 22);
            btnReset.Margin = new Padding(4, 3, 4, 3);
            btnReset.Name = "btnReset";
            btnReset.Size = new Size(182, 27);
            btnReset.TabIndex = 15;
            btnReset.Text = "Сбросить вид";
            btnReset.UseVisualStyleBackColor = true;
            btnReset.Click += btnReset_Click;

            btnMoveDown.Location = new Point(102, 126);
            btnMoveDown.Margin = new Padding(4, 3, 4, 3);
            btnMoveDown.Name = "btnMoveDown";
            btnMoveDown.Size = new Size(88, 27);
            btnMoveDown.TabIndex = 14;
            btnMoveDown.Text = "Вниз";
            btnMoveDown.UseVisualStyleBackColor = true;
            btnMoveDown.Click += btnMoveDown_Click;

            btnMoveUp.Location = new Point(7, 126);
            btnMoveUp.Margin = new Padding(4, 3, 4, 3);
            btnMoveUp.Name = "btnMoveUp";
            btnMoveUp.Size = new Size(88, 27);
            btnMoveUp.TabIndex = 13;
            btnMoveUp.Text = "Вверх";
            btnMoveUp.UseVisualStyleBackColor = true;
            btnMoveUp.Click += btnMoveUp_Click;

            btnMoveRight.Location = new Point(102, 92);
            btnMoveRight.Margin = new Padding(4, 3, 4, 3);
            btnMoveRight.Name = "btnMoveRight";
            btnMoveRight.Size = new Size(88, 27);
            btnMoveRight.TabIndex = 12;
            btnMoveRight.Text = "Вправо";
            btnMoveRight.UseVisualStyleBackColor = true;
            btnMoveRight.Click += btnMoveRight_Click;

            btnMoveLeft.Location = new Point(7, 92);
            btnMoveLeft.Margin = new Padding(4, 3, 4, 3);
            btnMoveLeft.Name = "btnMoveLeft";
            btnMoveLeft.Size = new Size(88, 27);
            btnMoveLeft.TabIndex = 11;
            btnMoveLeft.Text = "Влево";
            btnMoveLeft.UseVisualStyleBackColor = true;
            btnMoveLeft.Click += btnMoveLeft_Click;

            btnZoomOut.Location = new Point(102, 59);
            btnZoomOut.Margin = new Padding(4, 3, 4, 3);
            btnZoomOut.Name = "btnZoomOut";
            btnZoomOut.Size = new Size(88, 27);
            btnZoomOut.TabIndex = 10;
            btnZoomOut.Text = "Уменьшить";
            btnZoomOut.UseVisualStyleBackColor = true;
            btnZoomOut.Click += btnZoomOut_Click;

            btnZoomIn.Location = new Point(7, 59);
            btnZoomIn.Margin = new Padding(4, 3, 4, 3);
            btnZoomIn.Name = "btnZoomIn";
            btnZoomIn.Size = new Size(88, 27);
            btnZoomIn.TabIndex = 9;
            btnZoomIn.Text = "Увеличить";
            btnZoomIn.UseVisualStyleBackColor = true;
            btnZoomIn.Click += btnZoomIn_Click;
 
            label13.AutoSize = true;
            label13.Location = new Point(721, 718);
            label13.Margin = new Padding(4, 0, 4, 0);
            label13.Name = "label13";
            label13.Size = new Size(26, 15);
            label13.TabIndex = 10;
            label13.Text = "z = ";

            txtZ.Location = new Point(758, 714);
            txtZ.Margin = new Padding(4, 3, 4, 3);
            txtZ.Name = "txtZ";
            txtZ.Size = new Size(116, 23);
            txtZ.TabIndex = 11;
            txtZ.Text = "1";

            label4.AutoSize = true;
            label4.Location = new Point(124, 112);
            label4.Margin = new Padding(4, 0, 4, 0);
            label4.Name = "label4";
            label4.Size = new Size(14, 15);
            label4.TabIndex = 5;
            label4.Text = "Y";

            label6.AutoSize = true;
            label6.Location = new Point(124, 82);
            label6.Margin = new Padding(4, 0, 4, 0);
            label6.Name = "label6";
            label6.Size = new Size(14, 15);
            label6.TabIndex = 17;
            label6.Text = "Y";

            label8.AutoSize = true;
            label8.Location = new Point(124, 51);
            label8.Margin = new Padding(4, 0, 4, 0);
            label8.Name = "label8";
            label8.Size = new Size(14, 15);
            label8.TabIndex = 18;
            label8.Text = "Y";

            label10.AutoSize = true;
            label10.Location = new Point(124, 22);
            label10.Margin = new Padding(4, 0, 4, 0);
            label10.Name = "label10";
            label10.Size = new Size(14, 15);
            label10.TabIndex = 19;
            label10.Text = "Y";

            label14.AutoSize = true;
            label14.Location = new Point(48, 111);
            label14.Margin = new Padding(4, 0, 4, 0);
            label14.Name = "label14";
            label14.Size = new Size(14, 15);
            label14.TabIndex = 5;
            label14.Text = "X";
 
            label15.AutoSize = true;
            label15.Location = new Point(48, 82);
            label15.Margin = new Padding(4, 0, 4, 0);
            label15.Name = "label15";
            label15.Size = new Size(14, 15);
            label15.TabIndex = 20;
            label15.Text = "X";

            label16.AutoSize = true;
            label16.Location = new Point(48, 52);
            label16.Margin = new Padding(4, 0, 4, 0);
            label16.Name = "label16";
            label16.Size = new Size(14, 15);
            label16.TabIndex = 21;
            label16.Text = "X";

            label17.AutoSize = true;
            label17.Location = new Point(48, 21);
            label17.Margin = new Padding(4, 0, 4, 0);
            label17.Name = "label17";
            label17.Size = new Size(14, 15);
            label17.TabIndex = 22;
            label17.Text = "X";

            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(933, 750);
            Controls.Add(txtZ);
            Controls.Add(label13);
            Controls.Add(groupBox3);
            Controls.Add(groupBox2);
            Controls.Add(groupBox1);
            Controls.Add(btnSave);
            Controls.Add(label2);
            Controls.Add(txtIterations);
            Controls.Add(label1);
            Controls.Add(txtQ);
            Controls.Add(btnRun);
            Controls.Add(pictureBox);
            Margin = new Padding(4, 3, 4, 3);
            Name = "MainForm";
            Text = "Игра в Хаос";
            ((System.ComponentModel.ISupportInitialize)pictureBox).EndInit();
            groupBox1.ResumeLayout(false);
            groupBox1.PerformLayout();
            groupBox2.ResumeLayout(false);
            groupBox2.PerformLayout();
            groupBox3.ResumeLayout(false);
            ResumeLayout(false);
            PerformLayout();
        }

        private PictureBox pictureBox;
        private Button btnRun;
        private TextBox txtQ;
        private Label label1;
        private TextBox txtIterations;
        private Label label2;
        private Button btnSave;
        private GroupBox groupBox1;
        private Button btnSetVertices;
        private Label label9;
        private TextBox txtDY;
        private TextBox txtDX;
        private Label label7;
        private TextBox txtCY;
        private TextBox txtCX;
        private Label label5;
        private TextBox txtBY;
        private TextBox txtBX;
        private Label label3;
        private TextBox txtAY;
        private TextBox txtAX;
        private GroupBox groupBox2;
        private Button btnSetX0;
        private Label label12;
        private Label label11;
        private TextBox txtX0Y;
        private TextBox txtX0X;
        private GroupBox groupBox3;
        private Button btnReset;
        private Button btnMoveDown;
        private Button btnMoveUp;
        private Button btnMoveRight;
        private Button btnMoveLeft;
        private Button btnZoomOut;
        private Button btnZoomIn;
        private Label label13;
        private TextBox txtZ;
        private Label label17;
        private Label label16;
        private Label label15;
        private Label label14;
        private Label label10;
        private Label label8;
        private Label label6;
        private Label label4;
    }
}