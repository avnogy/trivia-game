using System;
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
using Newtonsoft.Json;
using Frontend.Requests;
using Frontend.Responses;
using Frontend.UI;

namespace Frontend
{
    /// <summary>
    /// Interaction logic for LoginWindow.xaml
    /// </summary>
    public partial class LoginWindow : Window
    {
        public LoginWindow()
        {
            InitializeComponent();
        }

        private void switchToSignup()
        {
            this.Hide();

            Window signupWindow = new SignupWindow();
            signupWindow.ShowDialog();

            this.Close();
        }

        private void switchToMenu()
        {
            this.Hide();

            Window menuWindow = new MenuWindow();
            menuWindow.ShowDialog();

            this.Close();
        }

        private void buttonSignup_Click(object sender, RoutedEventArgs e)
        {
            this.switchToSignup();
        }

        private void buttonSubmit_Click(object sender, RoutedEventArgs e)
        {
            //creating a json string representation of signup request
            LoginRequest loginRequest = new LoginRequest();
            loginRequest.username = textboxUsername.Text;
            loginRequest.password = textboxPassword.Text;
            String jsonRepr = JsonConvert.SerializeObject(loginRequest);

            //sending signup request
            Communicator.Send(Communicator.RequestType.LoginRequest, jsonRepr);

            //parsing signup response
            LoginResponse loginReponse = JsonConvert.DeserializeObject<LoginResponse>(Communicator.Receive());
            if (loginReponse.status == 0)
            {
                this.switchToMenu();
            }
            else
            {
                Label errorLabel = new Label();
                errorLabel.Name = "LabelError";
                errorLabel.Content = "You're not signed up yet.";
                errorLabel.Margin = new Thickness(30, 0, 30, 0);
                errorLabel.VerticalAlignment = VerticalAlignment.Bottom;
                errorLabel.HorizontalContentAlignment = HorizontalAlignment.Center;
                errorLabel.Foreground = Brushes.Black;
                errorLabel.Background = new SolidColorBrush(Color.FromArgb(0xFF, 0xFF, 0xCF, 0xCF));
                errorLabel.FontFamily = new FontFamily("Bell MT");
                errorLabel.FontSize = 12.5;

                Grid.SetRow(errorLabel, 0);
                Grid.SetColumnSpan(errorLabel, 3);
                Grid.Children.Add(errorLabel);
            }
        }
    }
}