using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Input;
using DevComponents.WpfRibbon;

namespace RibbonPad
{
    /// <summary>
    /// Defines the sample application commands used by the Ribbon Control.
    /// </summary>
    public class MyCommands
    {
        /// <summary>
        /// Defines Most Recently Used Item command.
        /// </summary>
        public static RoutedCommand MostRecentlyUsed = new RoutedCommand();

        /// <summary>
        /// Defines Close Document command. Note how Header and Images are set. They do not have to be set on ButtonDropDown instances that use this command since they will be
        /// automatically picked up.
        /// </summary>
        public static ButtonDropDownCommand CloseDocument = new ButtonDropDownCommand("Close", "closeDoc", "/images/FolderClosed32.png", typeof(Ribbon));

        /// <summary>
        /// Defines RibbonPad Options command.
        /// </summary>
        public static ButtonDropDownCommand Options = new ButtonDropDownCommand("Options", "options", "/images/Options.png", typeof(Ribbon));

        /// <summary>
        /// Defines Blue Color Scheme command.
        /// </summary>
        public static ButtonDropDownCommand BlueTheme = new ButtonDropDownCommand("Blue Theme", "blueTheme", "/images/SchemeBlue.png", "/images/SchemeBlue16.png", typeof(Ribbon));

        /// <summary>
        /// Defines Silver Color Scheme command.
        /// </summary>
        public static ButtonDropDownCommand SilverTheme = new ButtonDropDownCommand("Silver Theme", "silverTheme", "/images/SchemeSilver.png", "/images/SchemeSilver16.png", typeof(Ribbon));

        /// <summary>
        /// Defines Office 2010 Silver Color Scheme command.
        /// </summary>
        public static ButtonDropDownCommand Office2010SilverTheme = new ButtonDropDownCommand("2010 Silver", "Office2010silverTheme", "/images/SchemeSilver.png", "/images/SchemeSilver16.png", typeof(Ribbon));

        /// <summary>
        /// Defines Office 2010 Blue Color Scheme command.
        /// </summary>
        public static ButtonDropDownCommand Office2010BlueTheme = new ButtonDropDownCommand("2010 Blue", "Office2010BlueTheme", "/images/SchemeBlue.png", "/images/SchemeBlue16.png", typeof(Ribbon));

        /// <summary>
        /// Defines Office 2010 Black Color Scheme command.
        /// </summary>
        public static ButtonDropDownCommand Office2010BlackTheme = new ButtonDropDownCommand("2010 Black", "Office2010BlackTheme", "/images/SchemeBlack.png", "/images/SchemeBlack16.png", typeof(Ribbon));

        /// <summary>
        /// Defines Office 2013 Theme command.
        /// </summary>
        public static ButtonDropDownCommand Office2013Theme = new ButtonDropDownCommand("2013 Theme", "Office2013Theme", "/images/SchemeBlue2013.png", "/images/SchemeBlue201316.png", typeof(Ribbon));

        /// <summary>
        /// Defines Black Color Scheme command.
        /// </summary>
        public static ButtonDropDownCommand BlackTheme = new ButtonDropDownCommand("Black Theme", "blackTheme", "/images/SchemeBlack.png", "/images/SchemeBlack16.png", typeof(Ribbon));

        /// <summary>
        /// Defines Orange Color Scheme command.
        /// </summary>
        public static ButtonDropDownCommand OrangeTheme = new ButtonDropDownCommand("Aspect (Orange)", "orangeTheme", typeof(Ribbon));

        /// <summary>
        /// Defines Magenta Color Scheme command.
        /// </summary>
        public static ButtonDropDownCommand MagentaTheme = new ButtonDropDownCommand("Opulent (Magenta)", "magentaTheme", typeof(Ribbon));

        /// <summary>
        /// Defines Green Color Scheme command.
        /// </summary>
        public static ButtonDropDownCommand GreenTheme = new ButtonDropDownCommand("Foundry (Forest Green)", "greenTheme", typeof(Ribbon));

        /// <summary>
        /// Defines Dark Blue Color Scheme command.
        /// </summary>
        public static ButtonDropDownCommand DarkBlueTheme = new ButtonDropDownCommand("Midnight (Dark Blue)", "darkBlueTheme", typeof(Ribbon));

        /// <summary>
        /// Help Backstage Command.
        /// </summary>
        public static RoutedCommand HelpBackstage = new RoutedCommand("helpBackstage", typeof(Ribbon));

        /// <summary>
        /// Help KB Command.
        /// </summary>
        public static RoutedCommand HelpKB = new RoutedCommand("helpKB", typeof(Ribbon));

        /// <summary>
        /// Help Contact Command.
        /// </summary>
        public static RoutedCommand HelpContact = new RoutedCommand("helpContact", typeof(Ribbon));
       
    }
}
