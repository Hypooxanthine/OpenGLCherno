#pragma once

#include <cinttypes>
#include <vector>

#include "Vector.h"
#include "Drawable.h"

struct Vertex
{
    Vertex(const Vector3f& pos, const Vector3f& n) : position(pos), normal(n) {}
    Vertex() {}

    Vector3f position;
    Vector3f normal;

    static const long int POSITION_ATTRIB_INDEX = 0;
    static const long int POSITION_ATTRIB_OFFSET = 0;
    static const long int NORMAL_ATTRIB_INDEX = 1;
    static const long int NORMAL_ATTRIB_OFFSET = 1;
};

class Mesh : public IDrawable
{
public:
    Mesh();

    inline const Vertex* getVerticesData() const { return m_Vertices.data(); }
    inline const unsigned int* getIndicesData() const { return m_Indices.data(); }

    inline size_t getVerticesCount() const { return m_Vertices.size(); }
    inline size_t getTrianglesCount() const { return m_Indices.size() / 3; }

    bool loadFromFile(const std::string& path);
    void unload();

    void addVertex(const Vertex& v);
    void addVertex(Vertex&& v);

    void defineTriangle(int a, int b, int c);

    virtual void draw(Window& window) const override;

private:
    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices; // Indices stockés trois par trois.
};