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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Frontend.Pages
{
    /// <summary>
    /// Interaction logic for AddQuestion.xaml
    /// </summary>
    public partial class AddQuestion : Page
    {
        public AddQuestion()
        {
            InitializeComponent();
        }

        private void backBTN_Click(object sender, RoutedEventArgs e)
        {
            ((MainWindow)Application.Current.MainWindow).frame.Content = new MenuPage();
        }

        private void submitBTN_Click(object sender, RoutedEventArgs e)
        {
            if (questionTBX.Text == "" || rightAnswerTBX.Text == "" ||
                wrongAnswer1TBX.Text == "" || wrongAnswer2TBX.Text == "" ||
                wrongAnswer3TBX.Text == "")
            {
                MessageBox.Show("Fields can't be empty.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }


        }
    }
}
