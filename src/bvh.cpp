#include "bvh.h"
#include "util/qsplit.h"

BVH::BVH() {}

BVH::BVH(Shape** shapes, int num_shapes)
{
   if (num_shapes == 1) *this = BVH(shapes[0], shapes[0]);
   if (num_shapes == 2) *this = BVH(shapes[0], shapes[1]); 

   // find the midpoint of the bounding box to use as a qsplit pivot
   bbox = shapes[0]->boundingBox(0.0f, 0.0f);
   for (int i = 1; i < num_shapes; i++)
      bbox = surround(bbox, shapes[i]->boundingBox(0.0f, 0.0f));
   Vector3D pivot = (bbox.max() + bbox.min()) / 2.0f;
   
   int mid_point = qsplit(shapes, num_shapes, pivot.x(), 0);

   // create a new boundingVolume
   left  = buildBranch(shapes, mid_point, 1);
   right = buildBranch(&shapes[mid_point], num_shapes - mid_point, 1);
}

BVH::BVH(vector<Shape*>& shapesV)
{
   int num_shapes = shapesV.size();
   Shape** shapes;
   
   shapes = new Shape*[num_shapes];
   for (int i = 0; i < num_shapes; i++)
	  shapes[i] = shapesV[i];

   if (num_shapes == 1) *this = BVH(shapes[0], shapes[0]);
   if (num_shapes == 2) *this = BVH(shapes[0], shapes[1]); 

   // find the midpoint of the bounding box to use as a qsplit pivot
   bbox = shapes[0]->boundingBox(0.0f, 0.0f);
   for (int i = 1; i < num_shapes; i++)
      bbox = surround(bbox, shapes[i]->boundingBox(0.0f, 0.0f));
   Vector3D pivot = (bbox.max() + bbox.min()) / 2.0f;
   
   int mid_point = qsplit(shapes, num_shapes, pivot.x(), 0);
   // create a new boundingVolume
   left  = buildBranch(shapes, mid_point, 1);
   right = buildBranch(&shapes[mid_point], num_shapes - mid_point, 1);

}

BBox BVH::boundingBox( double time0, double time1 )const
{ return bbox; }

bool BVH::hit(const Ray& r, double tmin, double tmax, HitRecord& rec)const
{
   if (!(bbox.rayIntersect(r, tmin, tmax))) return false; 

   // else call hit on both branches
   bool isahit1 = false;
   bool isahit2 = false;
   rec.t = tmax;
   
   isahit1 = right->hit(r, tmin, tmax, rec);
   isahit2 = left->hit(r, tmin, rec.t, rec);

   return (isahit1 || isahit2);
}

bool BVH::shadowHit(const Ray& r, double tmin, double tmax, Material*& mat) const
{
   if (!(bbox.rayIntersect(r, tmin, tmax))) return false;
   
   if (right->shadowHit(r, tmin, tmax, mat)) return true;
   return  left->shadowHit(r, tmin, tmax, mat);
}

Shape* BVH::buildBranch (Shape** shapes, int shape_size, int axis) const
{
   if (shape_size == 1) return shapes[0];
   if (shape_size == 2) return (new BVH(shapes[0], shapes[1]));

   // find the midpoint of the bounding box to use as a qsplit pivot
   BBox box = shapes[0]->boundingBox(0.0f, 0.0f);
   for (int i = 1; i < shape_size; i++)
      box = surround(box, shapes[i]->boundingBox(0.0f, 0.0f));
   
   Vector3D pivot = (box.max() + box.min()) / 2.0f;

   // now split according to correct axis
   int mid_point = qsplit(shapes, shape_size, pivot[axis], axis);
  
   // create a new boundingVolume
   Shape* left  = buildBranch(shapes, mid_point, (axis + 1) % 3);
   Shape* right = buildBranch(&shapes[mid_point], shape_size-mid_point, (axis+1)%3);
   return new BVH(left, right, box);
}
