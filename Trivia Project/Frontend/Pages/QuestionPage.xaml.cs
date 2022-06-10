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

namespace Frontend
{
    /// <summary>
    /// Interaction logic for QuestionPage.xaml
    /// </summary>
    public partial class QuestionPage : Page
    {
        private Button[] buttons;

        public QuestionPage()
        {
            InitializeComponent();
            this.buttons = new Button[4];
            this.buttons[0] = choiceTopLeftBTN;
            this.buttons[1] = choiceTopRightBTN;
            this.buttons[2] = choiceBottomLeftBTN;
            this.buttons[3] = choiceBottomRightBTN;
        }

        private void select(int buttonIndex)
        {
            for (int i = 0; i < this.buttons.Length; i++)
            {
                if (i == buttonIndex) continue;
                this.buttons[i].Background = new BrushConverter().ConvertFrom("#FFABD3EF") as SolidColorBrush;
            }

            this.buttons[buttonIndex].Background = new BrushConverter().ConvertFrom("#FDFFB6") as SolidColorBrush;
        }

        private void choiceTopLeftBTN_Click(object sender, RoutedEventArgs e)
        {
            select(0);
        }

        private void choiceTopRightBTN_Click(object sender, RoutedEventArgs e)
        {
            select(1);
        }

        private void choiceBottomLeftBTN_Click(object sender, RoutedEventArgs e)
        {
            select(2);
        }

        private void choiceBottomRightBTN_Click(object sender, RoutedEventArgs e)
        {
            select(3);
        }
    }
}
