#include "Common.h"

using namespace std;

namespace Shape {

    class AbstractShape : public IShape {
    public:
        void SetPosition(Point new_position) override {
            position = new_position;
        }

        Point GetPosition() const override {
            return position;
        }

        void SetSize(Size new_size) override {
            size = new_size;
        }

        Size GetSize() const override {
            return size;
        }

        void SetTexture(std::shared_ptr<ITexture> new_texture) override {
            texture = new_texture;
        }

        ITexture *GetTexture() const override {
            return texture.get();
        }

    protected:
        Size GetTextureSize() const {
            return (texture ? texture->GetSize() : Size{0, 0});
        }

    protected:
        static const char empty = '.';
        Point position;
        Size size;
        shared_ptr<ITexture> texture;
    };

    class Rectangle : public AbstractShape {
    public:
        std::unique_ptr<IShape> Clone() const override {
            auto clone = make_unique<Rectangle>();
            clone->SetPosition(position);
            clone->SetSize(size);
            clone->SetTexture(texture);
            return clone;
        }

        void Draw(Image &img) const override {
            const auto &[texture_width, texture_height] = GetTextureSize();
            const auto &texture_image = (texture ? texture->GetImage() : Image());
            auto image_height = img.size();
            auto image_width = image_height != 0 ? img[0].size() : 0;
            for (int pos_y = position.y, y = 0; y < size.height; ++y) {
                for (int pos_x = position.x, x = 0; x < size.width; ++x) {
                    char point = empty;
                    if (texture) {
                        if (y < texture_height && x < texture_width)
                            point = texture_image[y][x];
                    }
                    if (pos_y + y < image_height && pos_x + x < image_width)
                        img[pos_y + y][pos_x + x] = point;
                }
            }
        }
    };

    class Ellipse : public AbstractShape {
        std::unique_ptr<IShape> Clone() const override {
            auto clone = make_unique<Ellipse>();
            clone->SetPosition(position);
            clone->SetSize(size);
            clone->SetTexture(texture);
            return clone;
        }

        void Draw(Image &img) const override {
            const auto &[texture_width, texture_height] = GetTextureSize();
            const auto &texture_image = (texture ? texture->GetImage() : Image());
            auto image_height = img.size();
            auto image_width = image_height != 0 ? img[0].size() : 0;
            for (int pos_y = position.y, y = 0; y < size.height; ++y) {
                for (int pos_x = position.x, x = 0; x < size.width; ++x) {
                    if (!IsPointInEllipse({x, y}, size))
                        continue;
                    char point = empty;
                    if (texture) {
                        if (y < texture_height && x < texture_width)
                            point = texture_image[y][x];
                    }
                    if (pos_y + y < image_height && pos_x + x < image_width)
                        img[pos_y + y][pos_x + x] = point;
                }
            }
        }
    };
}

unique_ptr<IShape> MakeShape(ShapeType shape_type) {
    switch (shape_type) {
        case ShapeType::Rectangle:
            return make_unique<Shape::Rectangle>();
        case ShapeType::Ellipse:
            return make_unique<Shape::Ellipse>();
        default:
            throw invalid_argument("");
    }
}