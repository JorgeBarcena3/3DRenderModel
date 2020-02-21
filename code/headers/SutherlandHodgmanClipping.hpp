#ifndef MATERIAL_HEADER
#define MATERIAL_HEADER

#include "Color_Buffer_Rgb565.hpp"
#include "Color_Buffer_Rgba8888.hpp"
#include "Model3D.hpp"

namespace RenderModel
{

    using toolkit::Point4f;
    using toolkit::Point4i;

    class SutherlandHodgmanClipping
    {
        typedef Point4i  Vertexi;
        typedef Point4f  Vertex;

    public:

        static void clip(const Point4i* const vertices, int* indices_begin, int* indices_end, int width, int height, vector<Point4i>& clipped_vertex)
        {

            vector< Point4i > intermediateVertices;
            vector< Point4i > finalVertices;

            for (int* i = indices_begin; i < indices_end; i++)
            {
                intermediateVertices.push_back(vertices[*i]);
            }

            xLeftClipping(intermediateVertices, height, finalVertices);
            resetClippingVector(intermediateVertices, finalVertices);

            yBottomClipping(intermediateVertices, width, finalVertices);
            resetClippingVector(intermediateVertices, finalVertices);

            xRightClipping(intermediateVertices, width, height, finalVertices);
            resetClippingVector(intermediateVertices, finalVertices);

            yTopClipping(intermediateVertices, height, width, finalVertices);

            clipped_vertex.swap(finalVertices);
        }


    private:

        static void yTopClipping(std::vector<toolkit::Point4i>& intermediateVertices, int height, int width, std::vector<toolkit::Point4i>& finalVertices)
        {
            //Limite de y superior
            for (size_t i = 0; i < intermediateVertices.size(); i++)
            {
                //Uno fuera y otro dentro
                if (intermediateVertices[i][1] > height&& intermediateVertices[(i + 1) >= intermediateVertices.size() ? 0 : i + 1][1] <= height)
                {
                    Vertex newVertice = line_intersection(Vertex({ 0,height }), Vertex({ width, height }), intermediateVertices[i], intermediateVertices[(i + 1) >= intermediateVertices.size() ? 0 : i + 1]);
                    finalVertices.push_back(Vertexi({ newVertice[0], newVertice[1], newVertice[2], newVertice[3] }));
                    finalVertices.push_back(intermediateVertices[(i + 1) >= intermediateVertices.size() ? 0 : i + 1]);

                }
                //Uno dentro y otro fuera
                else if (intermediateVertices[i][1] <= height && intermediateVertices[(i + 1) >= intermediateVertices.size() ? 0 : i + 1][1] > height)
                {
                    Vertex newVertice = line_intersection(Vertex({ 0,height }), Vertex({ width, height }), intermediateVertices[i], intermediateVertices[(i + 1) >= intermediateVertices.size() ? 0 : i + 1]);
                    finalVertices.push_back(Vertexi({ newVertice[0], newVertice[1], newVertice[2], newVertice[3] }));
                }
                // SI los dos estan dentro
                else if (intermediateVertices[i][1] <= height && intermediateVertices[(i + 1) >= intermediateVertices.size() ? 0 : i + 1][1] <= height)
                {
                    finalVertices.push_back(intermediateVertices[(i + 1) >= intermediateVertices.size() ? 0 : i + 1]);
                }

            }
        }

        static void xRightClipping(std::vector<toolkit::Point4i>& intermediateVertices, int width, int height, std::vector<toolkit::Point4i>& finalVertices)
        {
            //Limite de x superior
            for (size_t i = 0; i < intermediateVertices.size(); i++)
            {
                //Uno fuera y otro dentro
                if (intermediateVertices[i][0] > width&& intermediateVertices[(i + 1) >= intermediateVertices.size() ? 0 : i + 1][0] <= width)
                {
                    Vertex newVertice = line_intersection(Vertex({ width,0 }), Vertex({ width, height }), intermediateVertices[i], intermediateVertices[(i + 1) >= intermediateVertices.size() ? 0 : i + 1]);
                    finalVertices.push_back(Vertexi({ newVertice[0], newVertice[1], newVertice[2], newVertice[3] }));
                    finalVertices.push_back(intermediateVertices[(i + 1) >= intermediateVertices.size() ? 0 : i + 1]);

                }
                //Uno dentro y otro fuera
                else if (intermediateVertices[i][0] <= width && intermediateVertices[(i + 1) >= intermediateVertices.size() ? 0 : i + 1][0] > width)
                {
                    Vertex newVertice = line_intersection(Vertex({ width,0 }), Vertex({ width, height }), intermediateVertices[i], intermediateVertices[(i + 1) >= intermediateVertices.size() ? 0 : i + 1]);
                    finalVertices.push_back(Vertexi({ newVertice[0], newVertice[1], newVertice[2], newVertice[3] }));
                }
                // SI los dos estan dentro
                else if (intermediateVertices[i][0] <= width && intermediateVertices[(i + 1) >= intermediateVertices.size() ? 0 : i + 1][0] <= width)
                {
                    finalVertices.push_back(intermediateVertices[(i + 1) >= intermediateVertices.size() ? 0 : i + 1]);
                }

            }
        }

        static void yBottomClipping(std::vector<toolkit::Point4i>& intermediateVertices, int width, std::vector<toolkit::Point4i>& finalVertices)
        {
            //Limite de y inferior
            for (size_t i = 0; i < intermediateVertices.size(); i++)
            {
                //Uno fuera y otro dentro
                if (intermediateVertices[i][1] < 0 && intermediateVertices[(i + 1) >= intermediateVertices.size() ? 0 : i + 1][1] >= 0)
                {
                    Vertex newVertice = line_intersection(Vertex({ 0,0 }), Vertex({ width, 0 }), intermediateVertices[i], intermediateVertices[(i + 1) >= intermediateVertices.size() ? 0 : i + 1]);
                    finalVertices.push_back(Vertexi({ newVertice[0], newVertice[1], newVertice[2], newVertice[3] }));
                    finalVertices.push_back(intermediateVertices[(i + 1) >= intermediateVertices.size() ? 0 : i + 1]);

                }
                //Uno dentro y otro fuera
                else if (intermediateVertices[i][1] >= 0 && intermediateVertices[(i + 1) >= intermediateVertices.size() ? 0 : i + 1][1] < 0)
                {
                    Vertex newVertice = line_intersection(Vertex({ 0,0 }), Vertex({ width, 0 }), intermediateVertices[i], intermediateVertices[(i + 1) >= intermediateVertices.size() ? 0 : i + 1]);
                    finalVertices.push_back(Vertexi({ newVertice[0], newVertice[1], newVertice[2], newVertice[3] }));
                }
                // SI los dos estan dentro
                else if (intermediateVertices[i][1] >= 0 && intermediateVertices[(i + 1) >= intermediateVertices.size() ? 0 : i + 1][1] >= 0)
                {
                    finalVertices.push_back(intermediateVertices[(i + 1) >= intermediateVertices.size() ? 0 : i + 1]);
                }

            }
        }

        static void xLeftClipping(std::vector<toolkit::Point4i>& intermediateVertices, int height, std::vector<toolkit::Point4i>& finalVertices)
        {
            //Limite de x inferior
            for (size_t i = 0; i < intermediateVertices.size(); i++)
            {
                //Uno fuera y otro dentro
                if (intermediateVertices[i][0] < 0 && intermediateVertices[(i + 1) >= intermediateVertices.size() ? 0 : i + 1][0] >= 0)
                {
                    Vertex newVertice = line_intersection(Vertex({ 0,0 }), Vertex({ 0, height }), intermediateVertices[i], intermediateVertices[(i + 1) >= intermediateVertices.size() ? 0 : i + 1]);
                    finalVertices.push_back(Vertexi({ newVertice[0], newVertice[1], newVertice[2], newVertice[3] }));
                    finalVertices.push_back(intermediateVertices[(i + 1) >= intermediateVertices.size() ? 0 : i + 1]);

                }
                //Uno dentro y otro fuera
                else if (intermediateVertices[i][0] >= 0 && intermediateVertices[(i + 1) >= intermediateVertices.size() ? 0 : i + 1][0] < 0)
                {
                    Vertex newVertice = line_intersection(Vertex({ 0,0 }), Vertex({ 0, height }), intermediateVertices[i], intermediateVertices[(i + 1) >= intermediateVertices.size() ? 0 : i + 1]);
                    finalVertices.push_back(Vertexi({ newVertice[0], newVertice[1], newVertice[2], newVertice[3] }));
                }
                // SI los dos estan dentro
                else if (intermediateVertices[i][0] >= 0 && intermediateVertices[(i + 1) >= intermediateVertices.size() ? 0 : i + 1][0] >= 0)
                {
                    finalVertices.push_back(intermediateVertices[(i + 1) >= intermediateVertices.size() ? 0 : i + 1]);
                }

            }
        }


        static void resetClippingVector(vector< Point4i >& intermediateVertices, vector< Point4i >& finalVertices)
        {
            intermediateVertices.resize(finalVertices.size());
            std::copy(finalVertices.begin(), finalVertices.end(), intermediateVertices.begin());
            finalVertices.clear();
            finalVertices.resize(0);
        }

        static Vertex line_intersection(Vertex A, Vertex B, Vertexi C, Vertexi D)
        {

            float a1 = B[1] - A[1];
            float b1 = A[0] - B[0];
            float c1 = a1 * (A[0]) + b1 * (A[1]);

            float a2 = (float)(D[1] - C[1]);
            float b2 = (float)(C[0] - D[0]);
            float c2 = a2 * (C[0]) + b2 * (C[1]);


            float determinant = a1 * b2 - a2 * b1;

            if (determinant == 0)
            {
                return Point4f({ 0, 0, 1, 1 });
            }
            else
            {
                float x = (b2 * c1 - b1 * c2) / determinant;
                float y = (a1 * c2 - a2 * c1) / determinant;
                return Point4f({ x, y, 1, 1 });
            }

        };


    };

}

#endif
