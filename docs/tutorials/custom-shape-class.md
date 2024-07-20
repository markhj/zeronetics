@page custom-shape-class Custom shape as class

Creating a re-usable shape with customizable properties is
fairly easy with Zeronetics. To achieve this you extend ZEN::Shape3D
and implement ZEN::Shape3D::make.

## 🔷 Example

Let's say we want to crete a triangle where we can define the width
and height.

````cpp
class MyTriangle : public Shape3D {
public:
    MyTriangle(gw_float width, gw_float height) : m_width(width), m_height(height) {
        
    }

protected:
    [[nodiscard]] std::vector<Vertex3D> make() const noexcept override {
        std::vector<Vertex3D> result;
        
        gw_float hw = m_width / 2.0;
        gw_float hh = m_height / 2.0;
        
        result.push_back(Vertex3D{.position = {-w, -h, 0.0}});
        result.push_back(Vertex3D{.position = {w, -h, 0.0}});
        result.push_back(Vertex3D{.position = {0.0, h, 0.0}});
        
        return result;
    }

private:
    gw_float m_width, m_height;

};
````

What happens here is that we create three vertices will make up the
triangle.

The first vertex is the bottom-left corner, the second the bottom-right,
and the third is the top.

Remember that vertices must be given in counter-clockwise order.

![](https://res.cloudinary.com/drfztvfdh/image/upload/v1721454193/zeronetics/Custom_shape_-_Triangle_yonvjr.png)

## 📋 Notes

Remember to use ZEN::gw_float, because these are game world coordinates.

When the shape has been generated it will be stored in a private
property so it won't have to be re-computed on every request.

@important You must define your set of vertices such that their combined
center is at ``(0, 0, 0)``, otherwise using the positioning system in 
Zeronetics will produce unexpected results.

## 📌 See also

@ref custom-shape-vertices
