#ifndef SE_FILEFOLDERJSONDATA_H
#define SE_FILEFOLDERJSONDATA_H

#include <string>

namespace se
{
namespace priv
{
struct file_and_folder_data
{
	const char* scene_folder_name{ "scenes/" };					///Name of the folder containing scene files
	const char* scene_file_suffix{ ".json" };					///Suffix of the scene file
	const char* scene_names_file_name{ "scenenamelist.json" };	///Name of the file containing 
	const char* entity_tmpl_fold_name{ "entity_templates/" };	///Name of the folder containing entity template files

};

struct scene_file_structure
{
	const char* prim_obj_name{ "entities" };
	const char* info_obj_name{ "scene_info" };

	/*
	for example, scene file should look something like this:
	{
		"entities": {
			"player": {
				"some_component": {
					"some_value": 50.0
				}
			"enemy": {
				"some_component": {
					"some_value": 25.0
					}
				}
			}
		},
		"scene_info": {
		"heigth": 24,
		"width": 24
		"name": "level_1",
		"type": 2,
		}
	}
	*/
};

struct scene_names_file_structure
{
	const char* scenenamelist_obj_name = "scenenamelist";
	/*
	for example, scene names file should look something like this:
	{
		"scenenamelist": [
			"level_1",
			"level_2"
		]
	}
	*/
};

}//namespace priv	
}//namespace se

#endif