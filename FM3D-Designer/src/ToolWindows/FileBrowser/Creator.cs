using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FM3D_Designer.src.ToolWindows.FileBrowser
{
    public static class Creator
    {
        public static Item CreateItem(DirectoryInfo dirInfo, Project.Directory pFolder, Item parent)
        {
            if (parent == null)
                throw new ArgumentNullException("parent", "Item parent cannot be null. For root items use the other overloaded method.");

            return CreateItem(dirInfo, pFolder, parent.State, parent, parent.logic);
        }

        public static Item CreateItem(DirectoryInfo dirInfo, Project.Directory pFolder, Item.ItemState state, Item parent, Logic logic)
        {
            if (!dirInfo.Exists && state == Item.ItemState.NOT_PROJECT)
                throw new ArgumentException("Directory doesn't exist but is in a NOT_PROJECT content!");
            if (dirInfo.Exists && state == Item.ItemState.NOT_FOUND)
                throw new ArgumentException("Directory exists but is in a NOT_FOUND content!");

            var newState = GetNewItemState(dirInfo.Exists, state, pFolder != null);
            Item result = new Item(parent, logic, ItemTypes.Directory, dirInfo.Name, newState == Item.ItemState.NOT_FOUND ? null : dirInfo.FullName, newState);

            ObservableCollection<Project.Directory> folders = pFolder != null ? new ObservableCollection<Project.Directory>(pFolder.SubDirectories) : null;
            ObservableCollection<Project.File> files = pFolder != null ? new ObservableCollection<Project.File>(pFolder.Files) : null;
            try
            {
                foreach (var d in dirInfo.GetDirectories())
                {
                    if ((d.Attributes & FileAttributes.Hidden) == FileAttributes.Hidden)
                        continue;

                    Project.Directory folder = null;

                    if (pFolder != null)
                    {
                        foreach (var f in folders)
                        {
                            if (f.Name.Equals(d.Name))
                            {
                                folder = f;
                                folders.Remove(f);
                                break;
                            }
                        }
                    }

                    Item i = CreateItem(d, folder, result);
                    result.AddChildSilently(i);
                }
            }
            catch (UnauthorizedAccessException) { }
            catch (DirectoryNotFoundException) { }
            if (pFolder != null)
            {
                foreach (var f in folders)
                {
                    Item i = CreateItem(new DirectoryInfo(f.Path), f, result);
                    result.AddChildSilently(i);
                }
            }
            try
            {
                foreach (var f in dirInfo.GetFiles())
                {
                    bool inProj = false;
                    
                    if(pFolder != null)
                    {
                        foreach(var file in files)
                        {
                            if(file.Name.Equals(f.Name))
                            {
                                inProj = true;
                                files.Remove(file);
                                break;
                            }
                        }
                    }

                    Item i = CreateItem(f, result, inProj);
                    result.AddChildSilently(i);
                }
            }
            catch (UnauthorizedAccessException) { }
            catch (DirectoryNotFoundException) { }
            if (pFolder != null)
            {
                foreach (var file in files)
                {
                    Item i = CreateItem(new FileInfo(file.Path), result, true);
                    result.AddChildSilently(i);
                }
            }

            result.UpdateChildren();
            return result;
        }

        public static Item CreateItem(FileInfo fileInfo, Item parent, bool isInProject)
        {
            if (parent == null)
                throw new ArgumentNullException("parent", "Item parent cannot be null. Files cannot be used as root items!");


            var newState = GetNewItemState(fileInfo.Exists, parent.State, isInProject);
            Item result = new Item(parent, parent.logic, GetType(fileInfo.Extension), fileInfo.Name, newState == Item.ItemState.NOT_FOUND ? null : fileInfo.FullName, newState);
            return result;
        }

        private static Item.ItemState GetNewItemState(bool exists, Item.ItemState parentState, bool isInProject)
        {
            if (exists)
            {
                if (parentState == Item.ItemState.NORMAL && isInProject) return Item.ItemState.NORMAL;
                else return Item.ItemState.NOT_PROJECT;
            }
            else
                return Item.ItemState.NOT_FOUND;
        }

        private static ItemType GetType(string extension)
        {
            if (ItemTypes.FileTypes.ContainsKey(extension))
            {
                return ItemTypes.FileTypes[extension];
            }
            else
            {
                return ItemTypes.UnknownFile;
            }
        }
    }
}
