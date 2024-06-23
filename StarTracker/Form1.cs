using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace StarTracker
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        [DllImport("StarFinderLibrary.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        private static extern int TestFunc();
       

        private void button1_Click(object sender, EventArgs e)
        {
            int xSize = 700;
            int ySize = 700;
            String fileToDisplay = "star_image_1.bmp";
            Bitmap MyImage;
            pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
            MyImage = new Bitmap(fileToDisplay);
            pictureBox1.ClientSize = new Size(xSize, ySize);
            pictureBox1.Image = (Image)MyImage;

            int resp = TestFunc();
            label1.Text = resp.ToString();
        }
    }
}
