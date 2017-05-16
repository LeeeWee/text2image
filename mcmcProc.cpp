#include "mcmcProc.h"
#include <algorithm>
#include "adoPrcoess.h"
#include <ctime>

int initTypeIdMap(void)
{	
	//如果typeIdMap已经初始化过了，直接返回
	if (typeIdMap.size() != 0)
		return 0;

	//背景模板
	typeIdMap.insert(pair<string, int>("sky", 1));
	typeIdMap.insert(pair<string, int>("air", 1));
	typeIdMap.insert(pair<string, int>("subaerial", 1));
	typeIdMap.insert(pair<string, int>("aerial", 1));

	typeIdMap.insert(pair<string, int>("ground", 2));
	typeIdMap.insert(pair<string, int>("land", 2));
	typeIdMap.insert(pair<string, int>("dirt", 2));
	typeIdMap.insert(pair<string, int>("soil", 2));
	typeIdMap.insert(pair<string, int>("earth", 2));

	typeIdMap.insert(pair<string, int>("lawn", 3));
	typeIdMap.insert(pair<string, int>("grass", 3));
	typeIdMap.insert(pair<string, int>("grassland", 3));
	typeIdMap.insert(pair<string, int>("meadow", 3));
	typeIdMap.insert(pair<string, int>("greenward", 3));
	typeIdMap.insert(pair<string, int>("grassplot", 3));
	typeIdMap.insert(pair<string, int>("turf", 3));

	typeIdMap.insert(pair<string, int>("lake", 4));
	typeIdMap.insert(pair<string, int>("ness", 4));
	typeIdMap.insert(pair<string, int>("lough", 4));
	typeIdMap.insert(pair<string, int>("water", 4));
	typeIdMap.insert(pair<string, int>("sea", 4));

	typeIdMap.insert(pair<string, int>("road", 5));
	typeIdMap.insert(pair<string, int>("way", 5));
	typeIdMap.insert(pair<string, int>("route", 5));
	typeIdMap.insert(pair<string, int>("path", 5));
	typeIdMap.insert(pair<string, int>("highway", 5));
	typeIdMap.insert(pair<string, int>("trail", 5));
	typeIdMap.insert(pair<string, int>("trailway", 5));
	typeIdMap.insert(pair<string, int>("avenue", 5));
	typeIdMap.insert(pair<string, int>("pavement", 5));
	typeIdMap.insert(pair<string, int>("sidewalk", 5));
	typeIdMap.insert(pair<string, int>("lane", 5));
	typeIdMap.insert(pair<string, int>("trottoir", 5));

	//前景物体
	typeIdMap.insert(pair<string, int>("person", 11));
	typeIdMap.insert(pair<string, int>("man", 11));
	typeIdMap.insert(pair<string, int>("people", 11));
	typeIdMap.insert(pair<string, int>("body", 11));
	typeIdMap.insert(pair<string, int>("pedestrian", 11));
	typeIdMap.insert(pair<string, int>("player", 11));
	typeIdMap.insert(pair<string, int>("human", 11));
	typeIdMap.insert(pair<string, int>("guy", 11));
	typeIdMap.insert(pair<string, int>("staff", 11));
	typeIdMap.insert(pair<string, int>("chap", 11));

	typeIdMap.insert(pair<string, int>("vehicle", 12));
	typeIdMap.insert(pair<string, int>("car", 12));
	typeIdMap.insert(pair<string, int>("auto", 12));
	typeIdMap.insert(pair<string, int>("seater", 12));
	typeIdMap.insert(pair<string, int>("carriage", 12));
	typeIdMap.insert(pair<string, int>("sedan", 12));
	typeIdMap.insert(pair<string, int>("saloon", 12));
	typeIdMap.insert(pair<string, int>("van", 12));
	typeIdMap.insert(pair<string, int>("hatchback", 12));
	typeIdMap.insert(pair<string, int>("coupe", 12));
	typeIdMap.insert(pair<string, int>("suv", 12));
	typeIdMap.insert(pair<string, int>("pickup", 12));
	typeIdMap.insert(pair<string, int>("wagon", 12));
	typeIdMap.insert(pair<string, int>("roadster", 12));
	typeIdMap.insert(pair<string, int>("truck", 12));
	typeIdMap.insert(pair<string, int>("lorry", 12));
	typeIdMap.insert(pair<string, int>("convertible", 12));

	typeIdMap.insert(pair<string, int>("dog", 13));
	typeIdMap.insert(pair<string, int>("hound", 13));
	typeIdMap.insert(pair<string, int>("bitch", 13));
	typeIdMap.insert(pair<string, int>("puppy", 13));
	typeIdMap.insert(pair<string, int>("doggie", 13));
	typeIdMap.insert(pair<string, int>("mutt", 13));
	typeIdMap.insert(pair<string, int>("poodle", 13));
	typeIdMap.insert(pair<string, int>("cur", 13));

	typeIdMap.insert(pair<string, int>("cat", 14));
	typeIdMap.insert(pair<string, int>("bobcat", 14));
	typeIdMap.insert(pair<string, int>("siamese", 14));
	typeIdMap.insert(pair<string, int>("ragdoll", 14));
	typeIdMap.insert(pair<string, int>("persian", 14));

	typeIdMap.insert(pair<string, int>("airplane", 15));
	typeIdMap.insert(pair<string, int>("plane", 15));
	typeIdMap.insert(pair<string, int>("aircraft", 15));
	typeIdMap.insert(pair<string, int>("aeroplane", 15));
	typeIdMap.insert(pair<string, int>("drone", 15));
	typeIdMap.insert(pair<string, int>("spitfire", 15));
	typeIdMap.insert(pair<string, int>("conveyor", 15));
	typeIdMap.insert(pair<string, int>("aerobus", 15));
	typeIdMap.insert(pair<string, int>("jet", 15));
	typeIdMap.insert(pair<string, int>("airliner", 15));

	typeIdMap.insert(pair<string, int>("boat", 16));
	typeIdMap.insert(pair<string, int>("ship", 16));
	typeIdMap.insert(pair<string, int>("watercraft", 16));
	typeIdMap.insert(pair<string, int>("vessel", 16));
	typeIdMap.insert(pair<string, int>("steam", 16));
	typeIdMap.insert(pair<string, int>("steamership", 16));
	typeIdMap.insert(pair<string, int>("warship", 16));

	typeIdMap.insert(pair<string, int>("tree", 17));

	typeIdMap.insert(pair<string, int>("bicycle", 18));
	typeIdMap.insert(pair<string, int>("bike", 18));
	typeIdMap.insert(pair<string, int>("cycle", 18));

	typeIdMap.insert(pair<string, int>("duck", 19));
	typeIdMap.insert(pair<string, int>("tegel", 19));
	typeIdMap.insert(pair<string, int>("drake", 19));
	typeIdMap.insert(pair<string, int>("duckling", 19));
	typeIdMap.insert(pair<string, int>("teal", 19));

	typeIdMap.insert(pair<string, int>("cow", 20));
	typeIdMap.insert(pair<string, int>("bull ", 20));
	typeIdMap.insert(pair<string, int>("calf", 20));
	typeIdMap.insert(pair<string, int>("cattle", 20));
	typeIdMap.insert(pair<string, int>("buffalo", 20));
	typeIdMap.insert(pair<string, int>("ox", 20));
	typeIdMap.insert(pair<string, int>("yak", 20));
	typeIdMap.insert(pair<string, int>("bison", 20));

	typeIdMap.insert(pair<string, int>("horse", 21));
	typeIdMap.insert(pair<string, int>("mare", 21));
	typeIdMap.insert(pair<string, int>("stallion", 21));
	typeIdMap.insert(pair<string, int>("stud", 21));
	typeIdMap.insert(pair<string, int>("steed", 21));
	typeIdMap.insert(pair<string, int>("studhorse", 21));

	typeIdMap.insert(pair<string, int>("sheep", 22));
	typeIdMap.insert(pair<string, int>("mutton", 22));
	typeIdMap.insert(pair<string, int>("goat", 22));
	typeIdMap.insert(pair<string, int>("ram", 22));
	typeIdMap.insert(pair<string, int>("ewe", 22));
	typeIdMap.insert(pair<string, int>("lamb", 22));

	typeIdMap.insert(pair<string, int>("building", 23));
	typeIdMap.insert(pair<string, int>("arichitecture", 23));
	typeIdMap.insert(pair<string, int>("construction", 23));
	typeIdMap.insert(pair<string, int>("edifice", 23));
	typeIdMap.insert(pair<string, int>("block", 23));
	typeIdMap.insert(pair<string, int>("edificio", 23));
	typeIdMap.insert(pair<string, int>("house", 23));
	typeIdMap.insert(pair<string, int>("tenement", 23));
	typeIdMap.insert(pair<string, int>("cabin", 23));
	typeIdMap.insert(pair<string, int>("hut", 23));
	typeIdMap.insert(pair<string, int>("hovel", 23));
	typeIdMap.insert(pair<string, int>("lodge", 23));
	typeIdMap.insert(pair<string, int>("cabana", 23));
	typeIdMap.insert(pair<string, int>("hotel", 23));
	typeIdMap.insert(pair<string, int>("inn", 23));
	typeIdMap.insert(pair<string, int>("gasthaus", 23));
	typeIdMap.insert(pair<string, int>("station", 23));
	typeIdMap.insert(pair<string, int>("tavern", 23));
	typeIdMap.insert(pair<string, int>("caffe", 23));
	typeIdMap.insert(pair<string, int>("palace", 23));
	typeIdMap.insert(pair<string, int>("pavilion", 23));

	return 1;
}

int setPriority(void)
{
	priority.insert(pair<int, float>(11, (float)1.0));
	priority.insert(pair<int, float>(12, (float)0.4));
	priority.insert(pair<int, float>(13, (float)0.8));
	priority.insert(pair<int, float>(14, (float)0.8));
	priority.insert(pair<int, float>(15, (float)0.4));
	priority.insert(pair<int, float>(16, (float)0.4));
	priority.insert(pair<int, float>(17, (float)0.2));
	priority.insert(pair<int, float>(18, (float)0.4));
	priority.insert(pair<int, float>(19, (float)0.8));
	priority.insert(pair<int, float>(20, (float)0.6));
	priority.insert(pair<int, float>(21, (float)0.6));
	priority.insert(pair<int, float>(22, (float)0.6));
	priority.insert(pair<int, float>(23, (float)0.0));

	return 1;
}

int sceneDef(Scene scene)
{
	float Hori_Height;//地平线在图片上的百分比高度
	if (scene == SCENE_SKY){
		Hori_Height = 0;
		//Info info0 = { "sky", 1 };
		Object ob0("sky");
		Rect rect0(0, 0, Width, Height);
		ob0.rect = rect0;
		//defaultInfo.push_back(info0);
		bg_objects.push_back(ob0);
	}
	else if (scene == SCENE_LAWN){
		Hori_Height = 0.5;
		//Info info0 = { "sky", 1 };
		//Info info1 = { "lawn", 1 };
		Object ob0("sky");
		Rect rect0(Width * 0.5, (1 - Hori_Height) * Height * 0.5, Width, (1 - Hori_Height) * Height);
		ob0.rect = rect0;
		Object ob1("lawn");
		Rect rect1(Width * 0.5, (1 - 0.5 * Hori_Height) * Height, Width, Hori_Height * Height);
		ob1.rect = rect1;
		//defaultInfo.push_back(info0);
		//defaultInfo.push_back(info1);
		bg_objects.push_back(ob0);
		bg_objects.push_back(ob1);
	}
	else if (scene == SCENE_GROUND){
		Hori_Height = 0.4;
		//Info info0 = { "sky", 1 };
		//Info info1 = { "ground", 1 };
		Object ob0("sky");
		Rect rect0(Width * 0.5, (1 - Hori_Height) * Height * 0.5, Width, (1 - Hori_Height) * Height);
		ob0.rect = rect0;
		Object ob1("ground");
		Rect rect1(Width * 0.5, (1 - 0.5 * Hori_Height) * Height, Width, Hori_Height * Height);
		ob1.rect = rect1;
		//defaultInfo.push_back(info0);
		//defaultInfo.push_back(info1);
		bg_objects.push_back(ob0);
		bg_objects.push_back(ob1);
	}
	else if (scene == SCENE_SEA){
		Hori_Height = 0.5;
		//Info info0 = { "sky", 1 };
		//Info info1 = { "lake", 1 };
		Object ob0("sky");
		Rect rect0(Width * 0.5, (1 - Hori_Height) * Height * 0.5, Width, (1 - Hori_Height) * Height);
		ob0.rect = rect0;
		Object ob1("sea");
		Rect rect1(Width * 0.5, (1 - 0.5 * Hori_Height) * Height, Width, Hori_Height * Height);
		ob1.rect = rect1;
		//defaultInfo.push_back(info0);
		//defaultInfo.push_back(info1);
		bg_objects.push_back(ob0);
		bg_objects.push_back(ob1);
	}
	else if (scene == SCENE_STREET){
	//TODO
	}
	else if (scene == SCENE_GARDEN){
	//TODO
	}
	else if (scene == SCENE_FARM){
		Hori_Height = 0.5;
		//Info info0 = { "sky", 1 };
		//Info info1 = { "lawn", 1 };
		Info info3 = { "cow", 2 };
		Info info4 = { "sheep", 1 };
		Object ob0("sky");
		Rect rect0(Width * 0.5, (1 - Hori_Height) * Height * 0.5, Width, (1 - Hori_Height) * Height);
		ob0.rect = rect0;
		Object ob1("lawn");
		Rect rect1(Width * 0.5, (1 - 0.5 * Hori_Height) * Height, Width, Hori_Height * Height);
		ob1.rect = rect1;
		//defaultInfo.push_back(info0);
		//defaultInfo.push_back(info1);
		defaultInfo.push_back(info3);
		defaultInfo.push_back(info4);
		bg_objects.push_back(ob0);
		bg_objects.push_back(ob1);
	}
	_scene = scene;
	return 0;
}

//判断一个数组v2是否另一个数组v1的子集
bool isSubset(vector<int> v1, vector<int> v2){
	int i = 0, j = 0;
	int m = v1.size();
	int n = v2.size();
	if (m<n){
		return 0;
	}
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	while (i<n&&j<m){
		if (v1[j]<v2[i]){
			j++;
		}
		else if (v1[j] == v2[i]){
			j++;
			i++;
		}
		else if (v1[j]>v2[i]){
			return 0;
		}
	}
	if (i<n){
		return 0;
	}
	else{
		return 1;
	}
}

Scene sceneRecognize(vector<info> objInfo, vector<info> &objs)
{	
	initTypeIdMap();
	Scene scene = SCENE_WRONGSCENE;
	if (objInfo.size() == 1) { //输入语句中只有一个名词的情况下
		Info info = objInfo.at(0);
		if (typeIdMap[info.TypeName] >= 1 && typeIdMap[info.TypeName] <= 5) { //输入的一个名词是背景信息的时候
			if (typeIdMap[info.TypeName] == 1) {
				scene = SCENE_SKY;
			}
			else if (typeIdMap[info.TypeName] == 2) {
				scene = SCENE_GROUND;
			}
			else if (typeIdMap[info.TypeName] == 3) {
				scene = SCENE_LAWN;
			}
			else if (typeIdMap[info.TypeName] == 4) {
				scene = SCENE_SEA;
			}
			else {
				scene = SCENE_STREET;
			}
			sceneDef(scene);
			objs = defaultInfo;
			return scene;
		}
		else if (typeIdMap[info.TypeName] >= 11 && typeIdMap[info.TypeName] <= 23) { //输入的名词是前景物体信息的时候
			if (typeIdMap[info.TypeName] == 11 || typeIdMap[info.TypeName] == 12 || typeIdMap[info.TypeName] == 8) {
				scene = SCENE_GROUND;
			}
			else if (typeIdMap[info.TypeName] == 5) {
				scene = SCENE_SKY;
			}
			else if (typeIdMap[info.TypeName] == 6) {
				scene = SCENE_SEA;
			}
			else {
				scene = SCENE_LAWN;
			}
			sceneDef(scene);
			objs = objInfo;
			return scene;
		}
		else { //输入的名词没有匹配的typeId的时候
			if (info.TypeName == "street") {
				scene = SCENE_STREET;
			}
			else if (info.TypeName == "garden" || info.TypeName == "park") {
				scene = SCENE_GARDEN;
			}
			else if (info.TypeName == "farm" || info.TypeName == "farmland") {
				scene = SCENE_FARM;
			}
			else {
				cout << "无法生成匹配的图片！";
				return SCENE_WRONGSCENE;
			}
			sceneDef(scene);
			objs = defaultInfo;
			return scene;
		}
	}
	else {
		//不同场景中可能包含的背景和前景物体
		vector<int> sky_vector = { 1, 15 };
		vector<int> lawn_vector = { 1, 3, 11, 13, 14, 15, 17, 18, 19, 20, 21, 22, 23};
		vector<int> ground_vector = { 1, 2, 11, 12, 13, 14, 15, 18 };
		vector<int> sea_vector = { 1, 4, 15, 16, 19 };
		vector<int> street_vector = { 1, 5, 11, 12, 13, 14, 15, 18 };
		vector<int> garden_vector = { 1, 3, 4, 11, 12, 13, 14, 16, 17, 18, 19 };
		vector<int> farm_vector = { 1, 3, 11, 13, 14, 15, 17, 18, 19, 20, 21, 22, 23 };

		vector<int> object_vector;
		for (vector<info>::iterator iter = objInfo.begin(); iter != objInfo.end(); iter++) {
			if (iter->TypeName == "sea") {
				scene = SCENE_SEA;
			}
			if (iter->TypeName == "street") {
				scene = SCENE_STREET;
			}
			if (iter->TypeName == "garden" || iter->TypeName == "park") {
				scene = SCENE_GARDEN;
			}
			if (iter->TypeName == "farm" || iter->TypeName == "farmland") {
				scene = SCENE_FARM;
			}
			if (typeIdMap[iter->TypeName] >= 1 && typeIdMap[iter->TypeName] <= 23)
				object_vector.push_back(typeIdMap[iter->TypeName]);
		}
		if (scene == SCENE_WRONGSCENE) {
			if (isSubset(sky_vector, object_vector)) {
				scene = SCENE_SKY;
			}
			else if (isSubset(lawn_vector, object_vector)) {
				scene = SCENE_LAWN;
			}
			else if (isSubset(ground_vector, object_vector)) {
				scene = SCENE_GROUND;
			}
			else if (isSubset(sea_vector, object_vector)) {
				scene = SCENE_SEA;
			}
			else if (isSubset(street_vector, object_vector)) {
				scene = SCENE_STREET;
			}
			else if (isSubset(garden_vector, object_vector)) {
				scene = SCENE_GARDEN;
			}
			else if (isSubset(farm_vector, object_vector)) {
				scene = SCENE_FARM;
			}
		}
		sceneDef(scene);
		objs = defaultInfo;
		if (objs.size() == 0) {
			for (vector<info>::iterator iter = objInfo.begin(); iter != objInfo.end(); iter++) {
				if (typeIdMap[iter->TypeName] >= 11 && typeIdMap[iter->TypeName] <= 23) {
					objs.push_back(*iter);
				}
			}
		}
		else {
			vector<info>::iterator iter = objInfo.begin();
			while (iter != objInfo.end()) {
				if (typeIdMap[iter->TypeName] >= 11 && typeIdMap[iter->TypeName] <= 23) {
					vector<info>::iterator iter1 = objs.begin();
					while (iter1 != objs.end()) {
						if (iter1->TypeName == iter->TypeName) {
							iter1 = objs.erase(iter1);
						}
						else
							iter1++;
					}
					iter++;
				}
				else {
					iter = objInfo.erase(iter);
				}
			}
			objs.insert(objs.end(), objInfo.begin(), objInfo.end());
		}
		if (scene == SCENE_WRONGSCENE) {
			cout << "无法生成匹配的图片！";
		}
		return scene;
	}

}

int selectPictures(vector<info> objs)
{
	imagesetClassify(categories);
	//随机选取背景图片
	for (vector<Object>::iterator iter = bg_objects.begin(); iter != bg_objects.end(); iter++) {
		iter->imagesetId = randomSelect(categories[iter->typeId]);
		selectImage(&*iter);
	}
	//随机选取前景图片
	for (vector<info>::iterator iter = objs.begin(); iter != objs.end(); iter++) {
		int n = iter->ucount;
		int typeId = typeIdMap[iter->TypeName];
		vector<int> v;
		randomSelectN(n, categories[typeId], v);
		for (int i = 0; i < n; i++) {
			Object obj(iter->TypeName);
			obj.imagesetId = v[i];
			fg_objects.push_back(obj);
		}
	}
	for (vector<Object>::iterator iter = fg_objects.begin(); iter != fg_objects.end(); iter++) {
		selectImage(&*iter);
	}
	return 1;
}

//自定义排序函数,安照priority升序排序
bool sortObjByPriority(const Object obj1, const Object obj2)
{
	if (priority[obj1.typeId] < priority[obj2.typeId])
		return TRUE;
	else 
		return FALSE;
}

// 计算所有前景物体重叠面积
float calculateU(vector<Object> objects)
{
	float u = 0.0;
	int n = objects.size();
	if (n == 1)
		return 0;
	else {
		for (vector<Object>::iterator iter0 = objects.begin(); iter0 != objects.end() - 1; iter0++) {
			for (vector<Object>::iterator iter1 = iter0 + 1; iter1 != objects.end(); iter1++) {
				Rect rect0 = iter0->rect;
				Rect rect1 = iter1->rect;
				float overlapS = 0;
				float x1 = max(rect0.x - rect0.width * 0.5, rect1.x - rect1.width * 0.5);
				float x2 = min(rect0.x + rect0.width * 0.5, rect1.x + rect1.width * 0.5);
				float y1 = max(rect0.y - rect0.height * 0.5, rect1.y - rect1.height * 0.5);
				float y2 = min(rect0.y + rect0.height * 0.5, rect1.y + rect1.height * 0.5);
				if (x2 - x1 > 0 && y2 - y1 > 0)
					overlapS = (x2 - x1) * (y2 - y1);
				u += overlapS / (iter0->rect.width * iter0->rect.height)  * priority[iter0->typeId];
			}
		}
		u = (0 - u) / n;
		return u;
	}
}

//计算前景物体总面积和背景区域关系
float calculateG(vector<Object> objects)
{
	int n = fg_objects.size();
	float g = 0.0;
	for (vector<Object>::iterator iter0 = bg_objects.begin(); iter0 != bg_objects.end(); iter0++){
		for (vector<Object>::iterator iter1 = objects.begin(); iter1 != objects.end(); iter1++) {
			Rect rect0 = iter0->rect;
			Rect rect1 = iter1->rect;
			float overlapS = 0;
			float x1 = max(rect0.x - rect0.width * 0.5, rect1.x - rect1.width * 0.5);
			float x2 = min(rect0.x + rect0.width * 0.5, rect1.x + rect1.width * 0.5);
			float y1 = max(rect0.y - rect0.height * 0.5, rect1.y - rect1.height * 0.5);
			float y2 = min(rect0.y + rect0.height * 0.5, rect1.y + rect1.height * 0.5);
			if (x2 - x1 > 0 && y2 - y1 > 0)
				overlapS = (x2 - x1) * (y2 - y1);
			float r = relativity[iter0->typeId - 1][iter1->typeId - 11];
			g += overlapS / (iter1->rect.width * iter1->rect.height) * r;
		}
	}
	g /= n;
	return g;
}


//计算前景物体总面积和画面面积关系
float calculateF(vector<Object> objects)
{
	float S = 0;
	int n = fg_objects.size();
	for (vector<Object>::iterator iter = objects.begin(); iter != objects.end(); iter++) {
		S += iter->rect.width * iter->rect.height;
	}
	S = S  / (Width * Height);
	return S;
}

int mcmcProcess()
{
	int n = fg_objects.size();
	if (n == 0)
		return 0;

	srand(unsigned(time(NULL)));

	vector<float> v;
	for (vector<Object>::iterator iter = fg_objects.begin(); iter != fg_objects.end(); iter++) {
		v.push_back((Width / (iter->size_scale * iter->origin_size.width)));
		v.push_back((Height / (iter->size_scale * iter->origin_size.height)));
	}
	vector<float>::iterator max_iter = min_element(begin(v), end(v));
	//float scale = rand() % (int)(*max_iter * 100) / (float)100.0; //初始的基础宽度尺寸
	//float scale = 0.3 + rand() % 101 / (float)200.0; //初始的基础宽度尺寸
	float scale = 0.75 - 0.05 * n;
	std::cout << "scale:" << scale << endl;
	//随机设置前景物体的坐标和尺寸
	for (vector<Object>::iterator iter = fg_objects.begin(); iter != fg_objects.end(); iter++) {
		int obj_width = iter->size_scale * iter->origin_size.width * scale;
		int obj_height = iter->size_scale * iter->origin_size.height *scale;
		int x = rand() % (Width - obj_width) + obj_width * 0.5;
		int y = rand() % (Height - obj_height) + obj_height * 0.5;
		iter->rect = Rect(x, y, obj_width, obj_height);
	}
	//对vector按照前景物体优先级进行排序
	random_shuffle(fg_objects.begin(), fg_objects.end());
	sort(fg_objects.begin(), fg_objects.end(), sortObjByPriority);

	float k1 = 0.5, k2 = 2, k3 = 0.5;
	//TODO
	//MCMC迭代优化
	int t = 0; //限制物体尺寸单调变化参数
	int receive_count = 0;
	for (int i = 0; i < Itertions; i++) {
		float P = 1 + k1 * calculateU(fg_objects) + k1 * calculateG(fg_objects) + k1 * calculateF(fg_objects);
		if (i % 500 == 0){
			if (i == 0)
				std::cout << "mcmc_processing ";
			std::cout << "■";
			if (i == Itertions - 500) {
				std::cout << " PROCESS SUCESS!" << endl;
				std::cout << "==============================================" << endl;
			}
			//std::cout << "overlapS:" << calculateU(fg_objects) << " andS:" << calculateG(fg_objects) << " P(X):" << P << endl;
		}
		float q = 0;
		int k = rand() % 2;
		BOOL reception = TRUE;
		vector<Object> new_fg_objects = fg_objects;
		//放大或者缩小图片尺寸
		if (k == 0) {  
			//int zm = rand() % 2;
			//if (zm == 0) {  //放大图片尺寸
			//	scale += 0.1;
			//	if (scale < 0.3 || scale > 0.8) {
			//		reception = FALSE;
			//		scale -= 0.1;
			//	}
			//	for (vector<Object>::iterator iter = new_fg_objects.begin(); iter != new_fg_objects.end(); iter++) {
			//		int obj_width = iter->size_scale * iter->origin_size.width * scale;
			//		int obj_height = iter->size_scale * iter->origin_size.height *scale;
			//		iter->rect.width = obj_width;
			//		iter->rect.height = obj_height;
			//		if (iter->rect.x - 0.5 * obj_width <= 0 || iter->rect.x + 0.5 * obj_width >= Width
			//			|| iter->rect.y - 0.5 * obj_height <= 0 || iter->rect.y + 0.5 * obj_height >= Height){
			//			reception = FALSE;
			//			scale -= 0.1;
			//			break;
			//		}
			//	}
			//	if (t > 3) {
			//		q = 1 / 4;
			//		t++;
			//	}
			//	else if (t >= -3 && t <= 3) {
			//		q = 1;
			//		t++;
			//	}
			//	else {
			//		q = 1;
			//		t = 0;
			//	}
			//}
			//else {  //缩小图片尺寸
			//	scale -= 0.1;
			//	if (scale < 0.3 || scale > 0.8) {
			//		reception = FALSE;
			//		scale += 0.1;
			//	}
			//	for (vector<Object>::iterator iter = new_fg_objects.begin(); iter != new_fg_objects.end(); iter++) {
			//		int obj_width = iter->size_scale * iter->origin_size.width * scale;
			//		int obj_height = iter->size_scale * iter->origin_size.height *scale;
			//		iter->rect.width = obj_width;
			//		iter->rect.height = obj_height;
			//		if (iter->rect.x - 0.5 * iter->rect.width <= 0 || iter->rect.x + 0.5 * iter->rect.width >= Width
   //						|| iter->rect.y - 0.5 * iter->rect.height <= 0 || iter->rect.y + 0.5 * iter->rect.height >= Height
			//			|| iter->rect.width <= 0 || iter->rect.height <= 0){
			//			reception = FALSE;
			//			scale += 0.1;
			//			break;
			//		}
			//	}
			//	if (t < -3) {
			//		q = 1 / 4;
			//		t--;
			//	}
			//	else if (t >= -3 && t <= 3) {
			//		q = 1;
			//		t--;
			//	}
			//	else {
			//		q = 1;
			//		t = 0;
			//	}
			//}
			//float new_P = 1 + k1 * calculateU(new_fg_objects) + k1 * calculateG(new_fg_objects) + k1 * calculateF(new_fg_objects);
			//if (calculateG(fg_objects) >= 0.8 && calculateG(new_fg_objects) < calculateG(fg_objects))
			//	reception = FALSE;
			//float alpha = min((float)1, new_P * q / P);
			//float u = rand() % 100 / (float)99.0;
			//if (u < alpha && reception == TRUE){
			//	receive_count++;
			//	fg_objects = new_fg_objects;
			//}
		}
		else { //随机对一个前景物体进行移动
			int m = rand() % n; //选取第m个前景物体进行位置移动
			int n = rand() % 4;
			switch (n)
			{
			case 0:	
				new_fg_objects[m].rect.x += 30;
				break;
			case 1:
				new_fg_objects[m].rect.x -= 30;
				break;
			case 2:
				new_fg_objects[m].rect.y += 30;
				break;
			case 3:
				new_fg_objects[m].rect.y -= 30;
				break;
			}
			if (new_fg_objects[m].rect.x - 0.5 * new_fg_objects[m].rect.width <= 0 || new_fg_objects[m].rect.x + 0.5 * new_fg_objects[m].rect.width >= Width
				|| new_fg_objects[m].rect.y - 0.5 * new_fg_objects[m].rect.height <= 0 || new_fg_objects[m].rect.y + 0.5 * new_fg_objects[m].rect.height >= Height)
				reception = FALSE;
			float q0 = 1 - pow(((float)fg_objects[m].rect.x / Width - 0.5), 2) - pow(((float)fg_objects[m].rect.y / Height - 0.5), 2);
			float q1 = 1 - pow(((float)new_fg_objects[m].rect.x / Width - 0.5), 2) - pow(((float)new_fg_objects[m].rect.y / Height - 0.5), 2);
			float new_P = 1 + k1 * calculateU(new_fg_objects) + k1 * calculateG(new_fg_objects) + k1 * calculateF(new_fg_objects);
			if (calculateG(fg_objects) >= 0.8 && calculateG(new_fg_objects) < calculateG(fg_objects))
				reception = FALSE;
			if (calculateG(fg_objects) >= -0.3 && calculateG(new_fg_objects) < calculateG(fg_objects))
				reception = FALSE;
			float alpha = min((float)1, new_P * q1 / ( P *q0 ) );
			float u = rand() % 100 / (float)99.0;
			if (u < alpha && reception == TRUE ){
				receive_count++;
				fg_objects = new_fg_objects;
			}
		}
	}
	std::cout << "receive_count:" << receive_count << endl;
	std::cout << "scale:" << scale << endl;
	std::cout << "S/Sr:" << calculateF(fg_objects) << endl;

	//float P = 1 + k1 * calculateU(fg_objects) + k1 * calculateG(fg_objects) + k1 * calculateF(fg_objects);
	//std::cout << "overlapS:" << calculateU(fg_objects) << " andS:" << calculateG(fg_objects) << " P(X):" << P << endl;
	return 1;
}

int mcmc(vector<info> objInfo, vector<Object> &bg_objs, vector<Object> &fg_objs)
{
	vector<info> objs;
	Scene scene = sceneRecognize(objInfo, objs);
	if (scene == SCENE_WRONGSCENE)
		return 0;
	selectPictures(objs);
	setPriority();
	mcmcProcess();

	if (_scene == SCENE_GROUND){  //由于模板问题，调整ground的地平线高度
		float Hori_Height = 0.8;
		Rect rect(Width * 0.5, (1 - 0.5 * Hori_Height) * Height, Width, Hori_Height * Height);
		vector<Object>::iterator iter = bg_objects.begin() + 1;
		iter->rect = rect;
	}

	for (vector<Object>::iterator iter = bg_objects.begin(); iter != bg_objects.end(); iter++) {
		std::cout << iter->typeName << " TypeId:" << iter->typeId << " size:(" << iter->rect.x
			<< "," << iter->rect.y << "," << iter->rect.width << "," << iter->rect.height << ") imagesetId:"
			<< iter->imagesetId << endl;
	}
	for (vector<Object>::iterator iter = fg_objects.begin(); iter != fg_objects.end(); iter++) {
		std::cout << iter->typeName << " TypeId:" << iter->typeId << " size:(" << iter->rect.x
			<< "," << iter->rect.y << "," << iter->rect.width << "," << iter->rect.height << ") imagesetId:"
			<< iter->imagesetId << " SizeScale:" << iter->size_scale << endl;
	}
	std::cout << "==============================================" << endl;

	bg_objs = bg_objects;
	fg_objs = fg_objects;
	bg_objects.clear();
	fg_objects.clear();
	return 1;
}