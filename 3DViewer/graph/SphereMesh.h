#ifndef SPHEREMESH_H
#define SPHEREMESH_H

#include"Mesh.h"

namespace rtx
{
	namespace graph
	{
		class SphereMesh : public Mesh
		{

		public:

			SphereMesh()
			{
				int n = 64;
				int latitu = pow(n, 0.5), longitu = pow(n, 0.5);

				float rz1, rz2, rxy1, rxy2;
				float va, vb, vc, vd;
				glm::vec3 normal;
				for (size_t i = 0; i < longitu; i++)
				{
					for (size_t j = 0; j < latitu; j++)
					{
						rz1 = (Pi * j / latitu);
						rz2 = (Pi * (j + 1) / latitu);
						rxy1 = 2 * Pi * i / longitu;
						rxy2 = 2 * Pi * (i + 1) / longitu;
						va = { (double)R * sin(rz1) * cos(rxy1),(double)R * sin(rz1) * sin(rxy1),(double)R * cos(rz1) };
						vb = { (double)R * sin(rz2) * cos(rxy1),(double)R * sin(rz2) * sin(rxy1),(double)R * cos(rz2) };
						vc = { (double)R * sin(rz2) * cos(rxy2),(double)R * sin(rz2) * sin(rxy2),(double)R * cos(rz2) };
						vd = { (double)R * sin(rz1) * cos(rxy2),(double)R * sin(rz1) * sin(rxy2),(double)R * cos(rz1) };
						normal = Cross(vd - vb, va - vc).Normalize();
						
						glVertex3f(va.fX, va.fY, va.fZ);
						
						glVertex3f(vb.fX, vb.fY, vb.fZ);
						
						glVertex3f(vc.fX, vc.fY, vc.fZ);
						
						glVertex3f(vd.fX, vd.fY, vd.fZ);
					}
				}
			}

		};
	}
}

#endif // !SPHEREMESH_H
