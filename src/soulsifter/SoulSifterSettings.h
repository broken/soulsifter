//
//  SoulSifterSettings.h
//  soul-sifter
//
//  Created by Robby Neale on 12/9/12.
//
//

#ifndef __soul_sifter__SoulSifterSettings__
#define __soul_sifter__SoulSifterSettings__

#include <string>

#include <boost/property_tree/ptree.hpp>

namespace dogatech {
namespace soulsifter {
    
    class SoulSifterSettings {
    public:
        ~SoulSifterSettings() { }
        static SoulSifterSettings& getInstance() {
            static SoulSifterSettings instance;  // guaranteed to be destroyed
            // instantiated on first use
            return instance;
        }

        void save();

        template <typename T>
        const T get(const std::string& label) const;

        template <typename T>
        void put(const std::string& label, const T& value);
        
        /* deprecated */
        const std::string& getMusicPath() const { return musicPath; }
        void setMusicPath(const std::string& path) { musicPath = path; }
        const std::string& getREPath() const { return rePath; }
        void setREPath(const std::string& path) { rePath = path; }
        const std::string& getStagingPath() const { return stagingPath; }
        void setStagingPath(const std::string& path) { stagingPath = path; }
        
    private:
        // singleton
        SoulSifterSettings();
        SoulSifterSettings(SoulSifterSettings const&);
        void operator=(SoulSifterSettings const&);

        boost::property_tree::ptree ptree;

        std::string filename;
        
        /* deprecated */
        std::string musicPath;
        std::string rePath;
        std::string stagingPath;
    };
    
}
}

#endif /* defined(__soul_sifter__SoulSifterSettings__) */
