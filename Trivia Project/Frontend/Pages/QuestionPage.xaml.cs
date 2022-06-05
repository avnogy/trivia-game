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
        public QuestionPage()
        {
            InitializeComponent();
        }

        private void choiceTopLeftBTN_Click(object sender, RoutedEventArgs e)
        {
            //select
            choiceTopLeftBTN.Background = new BrushConverter().ConvertFrom("#FDFFB6") as SolidColorBrush;

            //deselect
            choiceTopRightBTN.Background = new BrushConverter().ConvertFrom("#FFABD3EF") as SolidColorBrush;
            choiceBottomLeftBTN.Background = new BrushConverter().ConvertFrom("#FFABD3EF") as SolidColorBrush;
            choiceBottomRightBTN.Background = new BrushConverter().ConvertFrom("#FFABD3EF") as SolidColorBrush;
        }

        private void choiceTopRightBTN_Click(object sender, RoutedEventArgs e)
        {
            //select
            choiceTopRightBTN.Background = new BrushConverter().ConvertFrom("#FDFFB6") as SolidColorBrush;

            //deselect
            choiceTopLeftBTN.Background = new BrushConverter().ConvertFrom("#FFABD3EF") as SolidColorBrush;
            choiceBottomLeftBTN.Background = new BrushConverter().ConvertFrom("#FFABD3EF") as SolidColorBrush;
            choiceBottomRightBTN.Background = new BrushConverter().ConvertFrom("#FFABD3EF") as SolidColorBrush;
        }

        private void choiceBottomLeftBTN_Click(object sender, RoutedEventArgs e)
        {

            //select
            choiceBottomLeftBTN.Background = new BrushConverter().ConvertFrom("#FDFFB6") as SolidColorBrush;

            //deselect
            choiceTopLeftBTN.Background = new BrushConverter().ConvertFrom("#FFABD3EF") as SolidColorBrush;
            choiceTopRightBTN.Background = new BrushConverter().ConvertFrom("#FFABD3EF") as SolidColorBrush;
            choiceBottomRightBTN.Background = new BrushConverter().ConvertFrom("#FFABD3EF") as SolidColorBrush;


        }

        private void choiceBottomRightBTN_Click(object sender, RoutedEventArgs e)
        {

            //select
            choiceBottomRightBTN.Background = new BrushConverter().ConvertFrom("#FDFFB6") as SolidColorBrush;

            //deselect
            choiceTopLeftBTN.Background = new BrushConverter().ConvertFrom("#FFABD3EF") as SolidColorBrush;
            choiceTopRightBTN.Background = new BrushConverter().ConvertFrom("#FFABD3EF") as SolidColorBrush;
            choiceBottomLeftBTN.Background = new BrushConverter().ConvertFrom("#FFABD3EF") as SolidColorBrush;

        }
    }
}
