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
using System.IO;

namespace StarTracker
{
    public partial class Form1 : Form
    {
        const string defaultImageName = "default_stars_image.bmp";
        const string baseClearImageName = "clear_image";
        const string resultFileName = "calc_result.txt";
        const int defaultLuminosityThreshold = 80;
        string inputFilename = defaultImageName;

        public Form1()
        {
            InitializeComponent();

            openFileDialog1.Filter = "Image Files(*.BMP)|*.BMP;";
            tbLuminosity.Text = defaultLuminosityThreshold.ToString();

            lFilename.Text = defaultImageName;
            calculateStarsInfo(defaultImageName);
        }

        [DllImport("StarFinderLibrary.dll", CharSet = CharSet.Ansi, SetLastError = true, CallingConvention = CallingConvention.Cdecl)]
        private static extern int SF_CalcStarsLocation(string inputBmpFile, string resultFile, string clearBmpFile, int luminosityThreshold);

        private void openFile_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.Cancel)
                return;
            inputFilename = System.IO.Path.GetFileName(openFileDialog1.FileName);
            lFilename.Text = inputFilename;

            calculateStarsInfo(inputFilename);
        }

        private void bUpdate_Click(object sender, EventArgs e)
        {
            calculateStarsInfo(inputFilename);
        }

        private void calculateStarsInfo(string inputImageFileName)
        {
            try
            {
                tbResult.Text = "";
                int calcResult = -1;
                int luminosityThreshold = defaultLuminosityThreshold;
                string clearImageName = createClearImageName();
                if (Int32.TryParse(tbLuminosity.Text, out luminosityThreshold))
                {
                    calcResult = SF_CalcStarsLocation(inputImageFileName, resultFileName, clearImageName, luminosityThreshold);
                } else
                {
                    tbResult.Text = "Error in luminosityThreshold value parsing";
                }

                showOriginalImage(inputImageFileName);
                if (calcResult == 0)
                {
                    showClearImage(clearImageName);
                    showCalcResult(resultFileName);     
                }
                else
                {
                    tbResult.Text = "Error in stars detection";
                }

            }
            catch (Exception ex)
            {
                tbResult.Text = "Exception:" + ex.ToString();
            }
        }

        private void showOriginalImage(string imageFileName)
        {
            int xSize = 500;
            int ySize = 500;
            Bitmap MyImage;
            pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
            MyImage = new Bitmap(imageFileName);
            pictureBox1.ClientSize = new Size(xSize, ySize);
            pictureBox1.Image = (Image)MyImage;
        }

        private void showClearImage(string imageFileName)
        {
            try
            {
                int xSize = 500;
                int ySize = 500;
                Bitmap MyImage;
                pictureBox2.SizeMode = PictureBoxSizeMode.StretchImage;
                MyImage = new Bitmap(imageFileName);
                pictureBox2.ClientSize = new Size(xSize, ySize);
                pictureBox2.Image = (Image)MyImage;
            }
            catch(Exception ex)
            {
                tbResult.Text = tbResult.Text + "Problem with clear image showing   ";
            }
        }

        private void showCalcResult(string resultFileName)
        {
            try
            {
                string data = File.ReadAllText(resultFileName);
                tbResult.Text = data;
            }
            catch (Exception ex)
            {
                tbResult.Text = tbResult.Text + "Problem with result data reading from file   ";
            }
        }

        private string createClearImageName()
        {
            Random rnd = new Random();
            int number = rnd.Next(100);
            string name = baseClearImageName + number.ToString() + ".bmp";
            return name;
        }
    }
}
