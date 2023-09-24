#include "Mesh.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "Util.h"

Mesh::Mesh()
{

}

bool Mesh::loadFromFile(const std::string& path)
{
    unload();

    std::ifstream ifs;

    ifs.open(path);

    if (!ifs.is_open())
    {
        std::cout << "Couldn't open \"" << path << "\"." << std::endl;
        ifs.close();
        return false;
    }

    std::string line;
    size_t lineNumber = 1;

    auto debugMesh = [&](const std::string& message) -> bool
    {
        std::cout << path << " - Error at line " << lineNumber << ": ";
        std::cout << message << std::endl;
        unload();

        return false;
    };

    while (!ifs.eof())
    {
        std::getline(ifs, line);

        // Removing inline comments
        auto commentPos = line.find("//", 0);
        if (commentPos != std::string::npos)
            line.erase(std::next(line.begin(), commentPos), line.end());

        Util::trim(line); // For beginning and ending spaces
        
        std::stringstream ss(line);
        std::string token;

        if (ss.eof()) continue;

        ss >> token;

        if (token == "v")
        {
            if (ss.eof())
                return debugMesh("A vertex needs a position and a normal vector.");

            Vertex vertex;
            bool positionOK = false, normalOK = false;


            while ((!positionOK || !normalOK) && !ss.eof())
            {
                ss >> token;

                if (token == "p")
                {
                    if (positionOK)
                        return debugMesh("A vertex must contain a single position attribute.");

                    for (uint8_t i = 0; i < 3; i++)
                    {
                        if (ss.eof())
                            return debugMesh("A position needs 3 coordinates.");

                        ss >> token;

                        try
                        {
                            reinterpret_cast<float*>(&vertex.position)[i] = std::stof(token);
                        }
                        catch (std::invalid_argument)
                        {
                            return debugMesh("Couldn't interpret position coordinate \"" + token + "\" as a float.");
                        }
                        catch (std::out_of_range)
                        {
                            return debugMesh("Position coordinate \"" + token + "\" is out of range of float type.");
                        }
                    }

                    positionOK = true;
                }
                else if (token == "n")
                {
                    if (normalOK)
                        return debugMesh("A vertex must contain a single normal attribute.");

                    for (uint8_t i = 0; i < 3; i++)
                    {
                        if (ss.eof())
                            return debugMesh("A normal vector needs 3 coordinates.");

                        ss >> token;

                        try
                        {
                            reinterpret_cast<float*>(&vertex.normal)[i] = std::stof(token);
                        }
                        catch (std::invalid_argument)
                        {
                            return debugMesh("Couldn't interpret normal coordinate \"" + token + "\" as a float.");
                        }
                        catch (std::out_of_range)
                        {
                            return debugMesh("Normal coordinate \"" + token + "\" is out of range of float type.");
                        }
                    }

                    normalOK = true;
                }
                else return debugMesh("Unexpected token \"" + token + "\".");
            }

            if (!normalOK || !positionOK)
                return debugMesh("A vertex needs a position and a normal attributes.");

            if (!ss.eof())
            {
                ss >> token;
                return debugMesh("Unexpected token \"" + token + "\".");
            }

            addVertex(std::move(vertex));
        }
        else if (token == "t")
        {
            int index[3] = { 0, 0, 0 };

            for (uint8_t i = 0; i < 3; i++)
            {
                if (ss.eof())
                    return debugMesh("A triangle needs 3 vertex indices.");

                ss >> token;

                try
                {
                    index[i] = std::stoi(token);
                }
                catch (std::invalid_argument)
                {
                    return debugMesh("Couldn't interpret triangle index \"" + token + "\" as an int.");
                }
                catch (std::out_of_range)
                {
                    return debugMesh("Triangle index \"" + token + "\" is out of range of int type.");
                }

                if (index[i] >= getVerticesCount())
                    return debugMesh("Vertex of index " + std::to_string(index[i]) + " is undefined. You need to define a vertex before assigning its index to a triangle.");
                else if (index[i] < 0)
                    return debugMesh("A vertex index must be positive.");
            }

            if (!ss.eof())
            {
                ss >> token;
                return debugMesh("Unexpected token \"" + token + "\".");
            }

            defineTriangle(index[0], index[1], index[2]);
        }
        else if (token != "")
            return debugMesh("Unexpected token \"" + token + "\"");

        lineNumber++;
    }

    ifs.close();
    return true;
}

void Mesh::unload()
{
    m_Vertices.clear();
    m_Indices.clear();
}

void Mesh::addVertex(const Vertex& v)
{
    m_Vertices.push_back(v);
}

void Mesh::addVertex(Vertex&& v)
{
    m_Vertices.push_back(std::move(v));
}

void Mesh::defineTriangle(int a, int b, int c)
{
    m_Indices.push_back(a);
    m_Indices.push_back(b);
    m_Indices.push_back(c);
}

void Mesh::draw(Window& window) const
{
    for(size_t i = 0 ; i < m_Indices.size() ; i += 3)
    {
        Vertex triangleBuffer[3] =
        {
            m_Vertices[m_Indices[i]],
            m_Vertices[m_Indices[i + 1]],
            m_Vertices[m_Indices[i + 2]]
        };

        unsigned int glBuffer;
        glGenBuffers(1, &glBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, glBuffer);
        glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(Vertex), triangleBuffer, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(Vertex::POSITION_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)Vertex::POSITION_ATTRIB_OFFSET);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glDisableVertexAttribArray(0);
        glDeleteBuffers(1, &glBuffer);
    }
}