using System;
using System.Drawing;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace ChaosGame
{
    public partial class MainForm : Form
    {
        private PointF[] vertices = new PointF[4];
        private PointF Xo;
        private float q = 0.5f;
        private int iterations = 300000;
        private Random random = new Random();
        private float z = 1.0f;
        private float scale = 1.0f;
        private PointF offset = new PointF(0, 0);


        private Bitmap canvas;
        private Graphics graphics;
        private Color pointColor = Color.MediumPurple;
        private Color vertexColor = Color.DeepPink;
        private int vertexSize = 3;

        public MainForm()
        {
            InitializeComponent();
            InitializeGame();
        }

        private void InitializeGame()
        {
            vertices[0] = new PointF(0, 0);
            vertices[1] = new PointF(1, 0);
            vertices[2] = new PointF(1, 1);
            vertices[3] = new PointF(0, 1);

            Xo = new PointF(0.5f, 0.5f);

            txtAX.Text = "0"; txtAY.Text = "0";
            txtBX.Text = "1"; txtBY.Text = "0";
            txtCX.Text = "0,7"; txtCY.Text = "1";
            txtDX.Text = "0,3"; txtDY.Text = "1";
            txtX0X.Text = "0,5"; txtX0Y.Text = "0,5";
            txtQ.Text = "0,5";
            txtIterations.Text = "500000";
            txtZ.Text = "1";

            canvas = new Bitmap(pictureBox.Width, pictureBox.Height);
            graphics = Graphics.FromImage(canvas);
            graphics.Clear(Color.White);

            DrawVertices();
            RunChaosGame();
        }

        private void DrawVertices()
        {
            graphics.Clear(Color.White);

            for (int i = 0; i < vertices.Length; i++)
            {
                PointF screenPoint = TransformToScreen(vertices[i]);
                graphics.FillEllipse(new SolidBrush(vertexColor),
                    screenPoint.X - vertexSize, screenPoint.Y - vertexSize,
                    vertexSize * 2, vertexSize * 2);
            }

            pictureBox.Image = canvas;
        }

        private PointF TransformToScreen(PointF point)
        {
            float x = (point.X - offset.X) * scale * pictureBox.Width / z;
            float y = pictureBox.Height - (point.Y - offset.Y) * scale * pictureBox.Height / z;
            return new PointF(x, y);
        }

        private void RunChaosGame()
        {
            PointF point = Xo;

            for (int i = 0; i < iterations; i++)
            {
                int randomVertex = random.Next(0, vertices.Length);
                PointF vertex = vertices[randomVertex];
                point = new PointF(
                    point.X + (vertex.X - point.X) * q,
                    point.Y + (vertex.Y - point.Y) * q);

                PointF screenPoint = TransformToScreen(point);
                if (screenPoint.X >= 0 && screenPoint.X < pictureBox.Width &&
                    screenPoint.Y >= 0 && screenPoint.Y < pictureBox.Height)
                {
                    canvas.SetPixel((int)screenPoint.X, (int)screenPoint.Y, pointColor);
                }

                if (i % 1000 == 0)
                {
                    pictureBox.Image = canvas;
                    Application.DoEvents();
                }
            }
            pictureBox.Image = canvas;
        }

        private void btnRun_Click(object sender, EventArgs e)
        {
            if (float.TryParse(txtQ.Text, out float newQ) && newQ > 0 && newQ < 1)
            {
                q = newQ;
            }

            if (float.TryParse(txtX0X.Text, out float x0x) && float.TryParse(txtX0Y.Text, out float x0y))
            {
                Xo = new PointF(x0x, x0y);
            }

            if (int.TryParse(txtIterations.Text, out int newIterations) && newIterations > 0)
            {
                iterations = newIterations;
            }
            else
            {
                MessageBox.Show("Количество итераций должно быть положительным числом");
                return;
            }

            if (float.TryParse(txtZ.Text, out float newZ) && newZ > 0)
            {
                z = newZ;
            }
            else
            {
                MessageBox.Show("z должно быть положительным числом");
                return;
            }

            DrawVertices();
            RunChaosGame();
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            using (SaveFileDialog saveDialog = new SaveFileDialog())
            {
                saveDialog.Filter = "JPEG Image|*.jpg";
                if (saveDialog.ShowDialog() == DialogResult.OK)
                {
                    canvas.Save(saveDialog.FileName, System.Drawing.Imaging.ImageFormat.Jpeg);
                }
            }
        }

        private void btnSetVertices_Click(object sender, EventArgs e)
        {
            if (float.TryParse(txtAX.Text, out float ax) && float.TryParse(txtAY.Text, out float ay))
                vertices[0] = new PointF(ax, ay);

            if (float.TryParse(txtBX.Text, out float bx) && float.TryParse(txtBY.Text, out float by))
                vertices[1] = new PointF(bx, by);

            if (float.TryParse(txtCX.Text, out float cx) && float.TryParse(txtCY.Text, out float cy))
                vertices[2] = new PointF(cx, cy);

            if (float.TryParse(txtDX.Text, out float dx) && float.TryParse(txtDY.Text, out float dy))
                vertices[3] = new PointF(dx, dy);

            DrawVertices();
        }

        private void btnSetX0_Click(object sender, EventArgs e)
        {
            if (float.TryParse(txtX0X.Text, out float x0x) && float.TryParse(txtX0Y.Text, out float x0y))
            {
                Xo = new PointF(x0x, x0y);
            }
        }

        private void btnZoomIn_Click(object sender, EventArgs e)
        {
            scale *= 1.2f;
            DrawVertices();
            RunChaosGame();
        }

        private void btnZoomOut_Click(object sender, EventArgs e)
        {
            scale /= 1.2f;
            DrawVertices();
            RunChaosGame();
        }

        private void btnMoveLeft_Click(object sender, EventArgs e)
        {
            offset.X += 0.1f / scale;
            DrawVertices();
            RunChaosGame();
        }

        private void btnMoveRight_Click(object sender, EventArgs e)
        {
            offset.X -= 0.1f / scale;
            DrawVertices();
            RunChaosGame();
        }

        private void btnMoveUp_Click(object sender, EventArgs e)
        {
            offset.Y -= 0.1f / scale;
            DrawVertices();
            RunChaosGame();
        }

        private void btnMoveDown_Click(object sender, EventArgs e)
        {
            offset.Y += 0.1f / scale;
            DrawVertices();
            RunChaosGame();
        }

        private void btnReset_Click(object sender, EventArgs e)
        {
            scale = 1.0f;
            offset = new PointF(0, 0);
            DrawVertices();
            RunChaosGame();
        }

    }
}