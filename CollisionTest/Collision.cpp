#include <SFML/Graphics.hpp>
#include "Collision.h"

using namespace sf;
using namespace std;

namespace Collision
{
    class BitmaskManager
    {
    public:
        ~BitmaskManager() {
            map < const Texture*, Uint8* > :: const_iterator end = Bitmasks.end();
            for (map<const Texture*, Uint8* > :: const_iterator iter = Bitmasks.begin(); iter != end; iter++)
                delete [] iter -> second;
        }

        Uint8 GetPixel (const Uint8* mask, const Texture* tex, unsigned int x, unsigned int y) {
            if (x > tex -> getSize().x || y > tex -> getSize().y)

            return 0;

            return mask[x + y * tex -> getSize().x];
        }

        Uint8* GetMask (const Texture* tex) {
            Uint8* mask;
            map < const Texture*, Uint8* > :: iterator pair = Bitmasks.find(tex);
            if (pair == Bitmasks.end())
            {
                Image img = tex -> copyToImage();
                mask = CreateMask(tex, img);
            }
            else
            mask = pair -> second;

            return mask;
        }

        Uint8* CreateMask (const Texture* tex, const Image& img) {
            Uint8* mask = new Uint8[tex -> getSize().y * tex -> getSize().x];

            for (unsigned int y = 0; y < tex -> getSize().y; y++)
            {
                for (unsigned int x = 0; x < tex -> getSize().x; x++)
                    mask[x + y * tex -> getSize().x] = img.getPixel(x,y).a;
            }

            Bitmasks.insert(pair < const Texture*, Uint8* > (tex,mask));

            return mask;
        }
    private:
        map < const Texture*, Uint8* > Bitmasks;
    };

    BitmaskManager Bitmasks;

    bool PixelPerfectTest(const Sprite& Object1, const Sprite& Object2, Uint8 AlphaLimit) {
        FloatRect Intersection;
        if (Object1.getGlobalBounds().intersects(Object2.getGlobalBounds(), Intersection)) {
            IntRect O1SubRect = Object1.getTextureRect();
            IntRect O2SubRect = Object2.getTextureRect();

            Uint8* mask1 = Bitmasks.GetMask(Object1.getTexture());
            Uint8* mask2 = Bitmasks.GetMask(Object2.getTexture());


            for (int i = Intersection.left; i < Intersection.left + Intersection.width; i++) {
                for (int j = Intersection.top; j < Intersection.top + Intersection.height; j++) {

                    Vector2f o1v = Object1.getInverseTransform().transformPoint(i, j);
                    Vector2f o2v = Object2.getInverseTransform().transformPoint(i, j);


                    if (o1v.x > 0 && o1v.y > 0 && o2v.x > 0 && o2v.y > 0 &&
                        o1v.x < O1SubRect.width && o1v.y < O1SubRect.height &&
                        o2v.x < O2SubRect.width && o2v.y < O2SubRect.height) {

                    if (Bitmasks.GetPixel(mask1, Object1.getTexture(), (int)(o1v.x) + O1SubRect.left, (int)(o1v.y) + O1SubRect.top) > AlphaLimit &&
                            Bitmasks.GetPixel(mask2, Object2.getTexture(), (int)(o2v.x) + O2SubRect.left, (int)(o2v.y) + O2SubRect.top) > AlphaLimit)

                            return true;

                    }
                }
            }
        }
        return false;
    }

    bool CreateTextureAndBitmask(Texture &LoadInto, const string& Filename)
    {
        Image img;
        if (!img.loadFromFile(Filename))

            return false;

        if (!LoadInto.loadFromImage(img))

            return false;

        Bitmasks.CreateMask(&LoadInto, img);

        return true;
    }

    Vector2f GetSpriteCenter(const Sprite& Object)
    {
        FloatRect AABB = Object.getGlobalBounds();

        return Vector2f(AABB.left + AABB.width / 2.0f, AABB.top + AABB.height / 2.0f);
    }

    Vector2f GetSpriteSize(const Sprite& Object)
    {
        IntRect OriginalSize = Object.getTextureRect();
        Vector2f Scale = Object.getScale();

        return Vector2f(OriginalSize.width * Scale.x, OriginalSize.height * Scale.y);
    }

    bool CircleTest(const Sprite& Object1, const Sprite& Object2) {
        Vector2f Obj1Size = GetSpriteSize(Object1);
        Vector2f Obj2Size = GetSpriteSize(Object2);

        float Radius1 = (Obj1Size.x + Obj1Size.y) / 4;
        float Radius2 = (Obj2Size.x + Obj2Size.y) / 4;

        Vector2f Distance = GetSpriteCenter(Object1) - GetSpriteCenter(Object2);

        return (Distance.x * Distance.x + Distance.y * Distance.y <= (Radius1 + Radius2) * (Radius1 + Radius2));
    }

    class OrientedBoundingBox
    {
    public:
        OrientedBoundingBox (const Sprite& Object)
        {
            Transform trans = Object.getTransform();
            IntRect local = Object.getTextureRect();
            Points[0] = trans.transformPoint(0.0f, 0.0f);
            Points[1] = trans.transformPoint(local.width, 0.0f);
            Points[2] = trans.transformPoint(local.width, local.height);
            Points[3] = trans.transformPoint(0.0f, local.height);
        }

        Vector2f Points[4];

        void ProjectOntoAxis (const Vector2f& Axis, float& Min, float& Max)
        {
            Min = (Points[0].x * Axis.x + Points[0].y * Axis.y);
            Max = Min;
            for (int j = 1; j < 4; j++)
            {
                float Projection = (Points[j].x * Axis.x + Points[j].y * Axis.y);

                if (Projection < Min)
                    Min = Projection;

                if (Projection > Max)
                    Max = Projection;
            }
        }
    };

    bool BoundingBoxTest(const Sprite& Object1, const Sprite& Object2) {
        OrientedBoundingBox OBB1(Object1);
        OrientedBoundingBox OBB2(Object2);


        Vector2f Axes[4] = {
            Vector2f(OBB1.Points[1].x - OBB1.Points[0].x,
                          OBB1.Points[1].y - OBB1.Points[0].y),
            Vector2f(OBB1.Points[1].x - OBB1.Points[2].x,
                          OBB1.Points[1].y - OBB1.Points[2].y),
            Vector2f(OBB2.Points[0].x - OBB2.Points[3].x,
                          OBB2.Points[0].y - OBB2.Points[3].y),
            Vector2f(OBB2.Points[0].x - OBB2.Points[1].x,
                          OBB2.Points[0].y - OBB2.Points[1].y)
        };

        for (int i = 0; i < 4; i++)
        {
            float MinOBB1, MaxOBB1, MinOBB2, MaxOBB2;


            OBB1.ProjectOntoAxis(Axes[i], MinOBB1, MaxOBB1);
            OBB2.ProjectOntoAxis(Axes[i], MinOBB2, MaxOBB2);


            if (!((MinOBB2 <= MaxOBB1) && (MaxOBB2 >= MinOBB1)))

                return false;
        }
        return true;
    }
}
