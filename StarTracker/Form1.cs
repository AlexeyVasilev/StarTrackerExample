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

        [DllImport("StarFinderLibrary.dll", CharSet = CharSet.Ansi, SetLastError = true, CallingConvention = CallingConvention.Cdecl)]
        private static extern int TestFunc();

        [DllImport("StarFinderLibrary.dll", CharSet = CharSet.Ansi, SetLastError = true, CallingConvention = CallingConvention.Cdecl)]
        private static extern int TestFunc_3(string a, string b);

        private void button1_Click(object sender, EventArgs e)
        {
            int xSize = 500;
            int ySize = 500;
            String fileToDisplay = "star_image_1.bmp";
            Bitmap MyImage;
            pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
            MyImage = new Bitmap(fileToDisplay);
            pictureBox1.ClientSize = new Size(xSize, ySize);
            pictureBox1.Image = (Image)MyImage;

            TestFunc_3("4855", "4977");

            int resp = TestFunc();
            lFilename.Text = resp.ToString();
        }
    }
}
