﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace Frontend
{
    /// <summary>
    /// Interaction logic for SignupWindow.xaml
    /// </summary>
    public partial class SignupWindow : Window
    {
        public SignupWindow()
        {
            InitializeComponent();
        }

        private void buttonLoginSignup_Click()
        {
        }

        private void buttonSignupLogin_Click(object sender, RoutedEventArgs e)
        {
            this.Hide();

            Window loginWindow = new LoginWindow();
            loginWindow.ShowDialog();

            this.Close();
        }
    }
}