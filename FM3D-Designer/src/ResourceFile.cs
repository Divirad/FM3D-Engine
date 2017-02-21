using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using FM3D_Designer.src.ToolWindows.FileBrowser;

namespace FM3D_Designer.src
{
    public class ResourceFile {

        private const string RESOURCE_CLASS = @"class Resources {
private:
	std::vector<FM3D::Texture*> m_textures;
	std::vector<FM3D::Mesh*> m_meshes;
	std::vector<FM3D::Model*> m_models;
	std::vector<FM3D::Skeleton*> m_skeleton;
	std::vector<FM3D::Material*> m_materials;
public:
	inline FM3D::Texture* GetTexture(uint id) { return m_textures[id]; }
	inline FM3D::Mesh* GetMesh(uint id) { return m_meshes[id]; }
	inline FM3D::Model* GetModel(uint id) { return m_models[id]; }
	inline FM3D::Skeleton* GetSkeleton(uint id) { return m_skeleton[id]; }
	inline FM3D::Material* GetMaterial(uint id) { return m_materials[id]; }

	void LoadResources();
};";

        public string Path { get; set; }

        public ResourceFile(string path)
        {
            this.Path = path;
        }

        public bool WriteFile()
        {
            try
            {
                using (StreamWriter file = new StreamWriter(Path))
                {
                    uint i = 0;
                    foreach(var f in Item.AllItems[ItemTypes.TextureFile])
                    {
                        file.WriteLine("#define TEXTURE_" + f.Name.ToUpper() + " " + i++.ToString());
                    }
                    i = 0;
                    foreach (var f in Item.AllItems[ItemTypes.MeshFile])
                    {
                        file.WriteLine("#define MESH_" + f.Name.ToUpper() + " " + i++.ToString());
                    }
                    i = 0;
                    foreach (var f in Item.AllItems[ItemTypes.ModelFile])
                    {
                        file.WriteLine("#define MODEL_" + f.Name.ToUpper() + " " + i++.ToString());
                    }
                    i = 0;
                    foreach (var f in Item.AllItems[ItemTypes.MaterialFile])
                    {
                        file.WriteLine("#define MATERIAL_" + f.Name.ToUpper() + " " + i++.ToString());
                    }
                    i = 0;
                    foreach (var f in Item.AllItems[ItemTypes.SkeletonFile])
                    {
                        file.WriteLine("#define SKELETON_" + f.Name.ToUpper() + " " + i++.ToString());
                    }
                }
            }
            catch
            {
                return false;
            }
            return true;
        }
    }
}
