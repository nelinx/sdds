/*
 * Geometry_PolygonExtrusion.c
 *
 *  Created on: Aug 2, 2016
 *      Author: o_dedi
 */

#include "sDDS.h"
#include "Geometry_PolygonExtrusion.h"

#ifdef FEATURE_SDDS_GEOMETRY_POLYGON_EXTRUSION_ENABLED

static bool_t
s_Point_equals(PolygonExtrusion_t* self, Point_t* otherObject);
static bool_t
s_Point_disjoint(PolygonExtrusion_t* self, Point_t* otherObject);
static bool_t
s_Point_intersects(PolygonExtrusion_t* self, Point_t* otherObject);
static bool_t
s_Point_touches(PolygonExtrusion_t* self, Point_t* otherObject);
static bool_t
s_Point_crosses(PolygonExtrusion_t* self, Point_t* otherObject);
static bool_t
s_Point_within(PolygonExtrusion_t* self, Point_t* otherObject);
static bool_t
s_Point_contains(PolygonExtrusion_t* self, Point_t* otherObject);
static bool_t
s_Point_overlaps(PolygonExtrusion_t* self, Point_t* otherObject);

static bool_t
s_LineString_equals(PolygonExtrusion_t* self, LineString_t* otherObject);
static bool_t
s_LineString_disjoint(PolygonExtrusion_t* self, LineString_t* otherObject);
static bool_t
s_LineString_intersects(PolygonExtrusion_t* self, LineString_t* otherObject);
static bool_t
s_LineString_touches(PolygonExtrusion_t* self, LineString_t* otherObject);
static bool_t
s_LineString_crosses(PolygonExtrusion_t* self, LineString_t* otherObject);
static bool_t
s_LineString_within(PolygonExtrusion_t* self, LineString_t* otherObject);
static bool_t
s_LineString_contains(PolygonExtrusion_t* self, LineString_t* otherObject);
static bool_t
s_LineString_overlaps(PolygonExtrusion_t* self, LineString_t* otherObject);

static bool_t
s_Line_equals(PolygonExtrusion_t* self, Line_t* otherObject);
static bool_t
s_Line_disjoint(PolygonExtrusion_t* self, Line_t* otherObject);
static bool_t
s_Line_intersects(PolygonExtrusion_t* self, Line_t* otherObject);
static bool_t
s_Line_touches(PolygonExtrusion_t* self, Line_t* otherObject);
static bool_t
s_Line_crosses(PolygonExtrusion_t* self, Line_t* otherObject);
static bool_t
s_Line_within(PolygonExtrusion_t* self, Line_t* otherObject);
static bool_t
s_Line_contains(PolygonExtrusion_t* self, Line_t* otherObject);
static bool_t
s_Line_overlaps(PolygonExtrusion_t* self, Line_t* otherObject);

static bool_t
s_LineRing_equals(PolygonExtrusion_t* self, LineRing_t* otherObject);
static bool_t
s_LineRing_disjoint(PolygonExtrusion_t* self, LineRing_t* otherObject);
static bool_t
s_LineRing_intersects(PolygonExtrusion_t* self, LineRing_t* otherObject);
static bool_t
s_LineRing_touches(PolygonExtrusion_t* self, LineRing_t* otherObject);
static bool_t
s_LineRing_crosses(PolygonExtrusion_t* self, LineRing_t* otherObject);
static bool_t
s_LineRing_within(PolygonExtrusion_t* self, LineRing_t* otherObject);
static bool_t
s_LineRing_contains(PolygonExtrusion_t* self, LineRing_t* otherObject);
static bool_t
s_LineRing_overlaps(PolygonExtrusion_t* self, LineRing_t* otherObject);

static bool_t
s_Polygon_equals(PolygonExtrusion_t* self, Polygon_t* otherObject);
static bool_t
s_Polygon_disjoint(PolygonExtrusion_t* self, Polygon_t* otherObject);
static bool_t
s_Polygon_intersects(PolygonExtrusion_t* self, Polygon_t* otherObject);
static bool_t
s_Polygon_touches(PolygonExtrusion_t* self, Polygon_t* otherObject);
static bool_t
s_Polygon_crosses(PolygonExtrusion_t* self, Polygon_t* otherObject);
static bool_t
s_Polygon_within(PolygonExtrusion_t* self, Polygon_t* otherObject);
static bool_t
s_Polygon_contains(PolygonExtrusion_t* self, Polygon_t* otherObject);
static bool_t
s_Polygon_overlaps(PolygonExtrusion_t* self, Polygon_t* otherObject);

static bool_t
s_Ellipse_equals(PolygonExtrusion_t* self, Ellipse_t* otherObject);
static bool_t
s_Ellipse_disjoint(PolygonExtrusion_t* self, Ellipse_t* otherObject);
static bool_t
s_Ellipse_intersects(PolygonExtrusion_t* self, Ellipse_t* otherObject);
static bool_t
s_Ellipse_touches(PolygonExtrusion_t* self, Ellipse_t* otherObject);
static bool_t
s_Ellipse_crosses(PolygonExtrusion_t* self, Ellipse_t* otherObject);
static bool_t
s_Ellipse_within(PolygonExtrusion_t* self, Ellipse_t* otherObject);
static bool_t
s_Ellipse_contains(PolygonExtrusion_t* self, Ellipse_t* otherObject);
static bool_t
s_Ellipse_overlaps(PolygonExtrusion_t* self, Ellipse_t* otherObject);

static bool_t
s_Square_equals(PolygonExtrusion_t* self, Square_t* otherObject);
static bool_t
s_Square_disjoint(PolygonExtrusion_t* self, Square_t* otherObject);
static bool_t
s_Square_intersects(PolygonExtrusion_t* self, Square_t* otherObject);
static bool_t
s_Square_touches(PolygonExtrusion_t* self, Square_t* otherObject);
static bool_t
s_Square_crosses(PolygonExtrusion_t* self, Square_t* otherObject);
static bool_t
s_Square_within(PolygonExtrusion_t* self, Square_t* otherObject);
static bool_t
s_Square_contains(PolygonExtrusion_t* self, Square_t* otherObject);
static bool_t
s_Square_overlaps(PolygonExtrusion_t* self, Square_t* otherObject);

static bool_t
s_PolyhedralSurface_equals(PolygonExtrusion_t* self, PolyhedralSurface_t* otherObject);
static bool_t
s_PolyhedralSurface_disjoint(PolygonExtrusion_t* self, PolyhedralSurface_t* otherObject);
static bool_t
s_PolyhedralSurface_intersects(PolygonExtrusion_t* self, PolyhedralSurface_t* otherObject);
static bool_t
s_PolyhedralSurface_touches(PolygonExtrusion_t* self, PolyhedralSurface_t* otherObject);
static bool_t
s_PolyhedralSurface_crosses(PolygonExtrusion_t* self, PolyhedralSurface_t* otherObject);
static bool_t
s_PolyhedralSurface_within(PolygonExtrusion_t* self, PolyhedralSurface_t* otherObject);
static bool_t
s_PolyhedralSurface_contains(PolygonExtrusion_t* self, PolyhedralSurface_t* otherObject);
static bool_t
s_PolyhedralSurface_overlaps(PolygonExtrusion_t* self, PolyhedralSurface_t* otherObject);

static bool_t
s_EllipseExtrusion_equals(PolygonExtrusion_t* self, EllipseExtrusion_t* otherObject);
static bool_t
s_EllipseExtrusion_disjoint(PolygonExtrusion_t* self, EllipseExtrusion_t* otherObject);
static bool_t
s_EllipseExtrusion_intersects(PolygonExtrusion_t* self, EllipseExtrusion_t* otherObject);
static bool_t
s_EllipseExtrusion_touches(PolygonExtrusion_t* self, EllipseExtrusion_t* otherObject);
static bool_t
s_EllipseExtrusion_crosses(PolygonExtrusion_t* self, EllipseExtrusion_t* otherObject);
static bool_t
s_EllipseExtrusion_within(PolygonExtrusion_t* self, EllipseExtrusion_t* otherObject);
static bool_t
s_EllipseExtrusion_contains(PolygonExtrusion_t* self, EllipseExtrusion_t* otherObject);
static bool_t
s_EllipseExtrusion_overlaps(PolygonExtrusion_t* self, EllipseExtrusion_t* otherObject);

static bool_t
s_SquareExtrusion_equals(PolygonExtrusion_t* self, SquareExtrusion_t* otherObject);
static bool_t
s_SquareExtrusion_disjoint(PolygonExtrusion_t* self, SquareExtrusion_t* otherObject);
static bool_t
s_SquareExtrusion_intersects(PolygonExtrusion_t* self, SquareExtrusion_t* otherObject);
static bool_t
s_SquareExtrusion_touches(PolygonExtrusion_t* self, SquareExtrusion_t* otherObject);
static bool_t
s_SquareExtrusion_crosses(PolygonExtrusion_t* self, SquareExtrusion_t* otherObject);
static bool_t
s_SquareExtrusion_within(PolygonExtrusion_t* self, SquareExtrusion_t* otherObject);
static bool_t
s_SquareExtrusion_contains(PolygonExtrusion_t* self, SquareExtrusion_t* otherObject);
static bool_t
s_SquareExtrusion_overlaps(PolygonExtrusion_t* self, SquareExtrusion_t* otherObject);

static bool_t
s_PolygonExtrusion_equals(PolygonExtrusion_t* self, PolygonExtrusion_t* otherObject);
static bool_t
s_PolygonExtrusion_disjoint(PolygonExtrusion_t* self, PolygonExtrusion_t* otherObject);
static bool_t
s_PolygonExtrusion_intersects(PolygonExtrusion_t* self, PolygonExtrusion_t* otherObject);
static bool_t
s_PolygonExtrusion_touches(PolygonExtrusion_t* self, PolygonExtrusion_t* otherObject);
static bool_t
s_PolygonExtrusion_crosses(PolygonExtrusion_t* self, PolygonExtrusion_t* otherObject);
static bool_t
s_PolygonExtrusion_within(PolygonExtrusion_t* self, PolygonExtrusion_t* otherObject);
static bool_t
s_PolygonExtrusion_contains(PolygonExtrusion_t* self, PolygonExtrusion_t* otherObject);
static bool_t
s_PolygonExtrusion_overlaps(PolygonExtrusion_t* self, PolygonExtrusion_t* otherObject);

static bool_t
s_PolyhedralSurfaceExtrusion_equals(PolygonExtrusion_t* self, PolyhedralSurfaceExtrusion_t* otherObject);
static bool_t
s_PolyhedralSurfaceExtrusion_disjoint(PolygonExtrusion_t* self, PolyhedralSurfaceExtrusion_t* otherObject);
static bool_t
s_PolyhedralSurfaceExtrusion_intersects(PolygonExtrusion_t* self, PolyhedralSurfaceExtrusion_t* otherObject);
static bool_t
s_PolyhedralSurfaceExtrusion_touches(PolygonExtrusion_t* self, PolyhedralSurfaceExtrusion_t* otherObject);
static bool_t
s_PolyhedralSurfaceExtrusion_crosses(PolygonExtrusion_t* self, PolyhedralSurfaceExtrusion_t* otherObject);
static bool_t
s_PolyhedralSurfaceExtrusion_within(PolygonExtrusion_t* self, PolyhedralSurfaceExtrusion_t* otherObject);
static bool_t
s_PolyhedralSurfaceExtrusion_contains(PolygonExtrusion_t* self, PolyhedralSurfaceExtrusion_t* otherObject);
static bool_t
s_PolyhedralSurfaceExtrusion_overlaps(PolygonExtrusion_t* self, PolyhedralSurfaceExtrusion_t* otherObject);


/******************************************************
 *                  Implementation
 ******************************************************/

bool_t
PolygonExtrusion_equals(PolygonExtrusion_t* self, Geometry_t* otherObject) {
    switch (otherObject->type) {
    case GEO_TYPE_POINT:
        return s_Point_equals(self, (Point_t*)otherObject);

    case GEO_TYPE_LINESTRING:
        return s_LineString_equals(self, (LineString_t*)otherObject);

    case GEO_TYPE_LINE:
        return s_Line_equals(self, (Line_t*)otherObject);

    case GEO_TYPE_LINERING:
        return s_LineRing_equals(self, (LineRing_t*)otherObject);

    case GEO_TYPE_ELLIPSE:
        return s_Ellipse_equals(self, (Ellipse_t*)otherObject);

    case GEO_TYPE_SQUARE:
        return s_Square_equals(self, (Square_t*)otherObject);

    case GEO_TYPE_POLYGON:
        return s_Polygon_equals(self, (Polygon_t*)otherObject);

    case GEO_TYPE_POLYHEDRALSURFACE:
        return s_PolyhedralSurface_equals(self, (PolyhedralSurface_t*)otherObject);

    case GEO_TYPE_ELLIPSE_EXTRUSION:
        return s_EllipseExtrusion_equals(self, (EllipseExtrusion_t*)otherObject);

    case GEO_TYPE_SQUARE_EXTRUSION:
        return s_SquareExtrusion_equals(self, (SquareExtrusion_t*)otherObject);

    case GEO_TYPE_POLYGON_EXTRUSION:
        return s_PolygonExtrusion_equals(self, (PolygonExtrusion_t*)otherObject);

    case GEO_TYPE_POLYHEDRALSURFACE_EXTRUSION:
        return s_PolyhedralSurfaceExtrusion_equals(self, (PolyhedralSurfaceExtrusion_t*)otherObject);

    default:
        return false;
    }
}

bool_t
PolygonExtrusion_disjoint(PolygonExtrusion_t* self, Geometry_t* otherObject) {
    switch (otherObject->type) {
    case GEO_TYPE_POINT:
        return s_Point_disjoint(self, (Point_t*)otherObject);

    case GEO_TYPE_LINESTRING:
        return s_LineString_disjoint(self, (LineString_t*)otherObject);

    case GEO_TYPE_LINE:
        return s_Line_disjoint(self, (Line_t*)otherObject);

    case GEO_TYPE_LINERING:
        return s_LineRing_disjoint(self, (LineRing_t*)otherObject);

    case GEO_TYPE_ELLIPSE:
        return s_Ellipse_disjoint(self, (Ellipse_t*)otherObject);

    case GEO_TYPE_SQUARE:
        return s_Square_disjoint(self, (Square_t*)otherObject);

    case GEO_TYPE_POLYGON:
        return s_Polygon_disjoint(self, (Polygon_t*)otherObject);

    case GEO_TYPE_POLYHEDRALSURFACE:
        return s_PolyhedralSurface_disjoint(self, (PolyhedralSurface_t*)otherObject);

    case GEO_TYPE_ELLIPSE_EXTRUSION:
        return s_EllipseExtrusion_disjoint(self, (EllipseExtrusion_t*)otherObject);

    case GEO_TYPE_SQUARE_EXTRUSION:
        return s_SquareExtrusion_disjoint(self, (SquareExtrusion_t*)otherObject);

    case GEO_TYPE_POLYGON_EXTRUSION:
        return s_PolygonExtrusion_disjoint(self, (PolygonExtrusion_t*)otherObject);

    case GEO_TYPE_POLYHEDRALSURFACE_EXTRUSION:
        return s_PolyhedralSurfaceExtrusion_disjoint(self, (PolyhedralSurfaceExtrusion_t*)otherObject);

    default:
        return false;
    }
}

bool_t
PolygonExtrusion_intersects(PolygonExtrusion_t* self, Geometry_t* otherObject) {
    switch (otherObject->type) {
    case GEO_TYPE_POINT:
        return s_Point_intersects(self, (Point_t*)otherObject);

    case GEO_TYPE_LINESTRING:
        return s_LineString_intersects(self, (LineString_t*)otherObject);

    case GEO_TYPE_LINE:
        return s_Line_intersects(self, (Line_t*)otherObject);

    case GEO_TYPE_LINERING:
        return s_LineRing_intersects(self, (LineRing_t*)otherObject);

    case GEO_TYPE_ELLIPSE:
        return s_Ellipse_intersects(self, (Ellipse_t*)otherObject);

    case GEO_TYPE_SQUARE:
        return s_Square_intersects(self, (Square_t*)otherObject);

    case GEO_TYPE_POLYGON:
        return s_Polygon_intersects(self, (Polygon_t*)otherObject);

    case GEO_TYPE_POLYHEDRALSURFACE:
        return s_PolyhedralSurface_intersects(self, (PolyhedralSurface_t*)otherObject);

    case GEO_TYPE_ELLIPSE_EXTRUSION:
        return s_EllipseExtrusion_intersects(self, (EllipseExtrusion_t*)otherObject);

    case GEO_TYPE_SQUARE_EXTRUSION:
        return s_SquareExtrusion_intersects(self, (SquareExtrusion_t*)otherObject);

    case GEO_TYPE_POLYGON_EXTRUSION:
        return s_PolygonExtrusion_intersects(self, (PolygonExtrusion_t*)otherObject);

    case GEO_TYPE_POLYHEDRALSURFACE_EXTRUSION:
        return s_PolyhedralSurfaceExtrusion_intersects(self, (PolyhedralSurfaceExtrusion_t*)otherObject);

    default:
        return false;
    }
}

bool_t
PolygonExtrusion_touches(PolygonExtrusion_t* self, Geometry_t* otherObject) {
    switch (otherObject->type) {
    case GEO_TYPE_POINT:
        return s_Point_touches(self, (Point_t*)otherObject);

    case GEO_TYPE_LINESTRING:
        return s_LineString_touches(self, (LineString_t*)otherObject);

    case GEO_TYPE_LINE:
        return s_Line_touches(self, (Line_t*)otherObject);

    case GEO_TYPE_LINERING:
        return s_LineRing_touches(self, (LineRing_t*)otherObject);

    case GEO_TYPE_ELLIPSE:
        return s_Ellipse_touches(self, (Ellipse_t*)otherObject);

    case GEO_TYPE_SQUARE:
        return s_Square_touches(self, (Square_t*)otherObject);

    case GEO_TYPE_POLYGON:
        return s_Polygon_touches(self, (Polygon_t*)otherObject);

    case GEO_TYPE_POLYHEDRALSURFACE:
        return s_PolyhedralSurface_touches(self, (PolyhedralSurface_t*)otherObject);

    case GEO_TYPE_ELLIPSE_EXTRUSION:
        return s_EllipseExtrusion_touches(self, (EllipseExtrusion_t*)otherObject);

    case GEO_TYPE_SQUARE_EXTRUSION:
        return s_SquareExtrusion_touches(self, (SquareExtrusion_t*)otherObject);

    case GEO_TYPE_POLYGON_EXTRUSION:
        return s_PolygonExtrusion_touches(self, (PolygonExtrusion_t*)otherObject);

    case GEO_TYPE_POLYHEDRALSURFACE_EXTRUSION:
        return s_PolyhedralSurfaceExtrusion_touches(self, (PolyhedralSurfaceExtrusion_t*)otherObject);

    default:
        return false;
    }
}

bool_t
PolygonExtrusion_crosses(PolygonExtrusion_t* self, Geometry_t* otherObject) {
    switch (otherObject->type) {
    case GEO_TYPE_POINT:
        return s_Point_crosses(self, (Point_t*)otherObject);

    case GEO_TYPE_LINESTRING:
        return s_LineString_crosses(self, (LineString_t*)otherObject);

    case GEO_TYPE_LINE:
        return s_Line_crosses(self, (Line_t*)otherObject);

    case GEO_TYPE_LINERING:
        return s_LineRing_crosses(self, (LineRing_t*)otherObject);

    case GEO_TYPE_ELLIPSE:
        return s_Ellipse_crosses(self, (Ellipse_t*)otherObject);

    case GEO_TYPE_SQUARE:
        return s_Square_crosses(self, (Square_t*)otherObject);

    case GEO_TYPE_POLYGON:
        return s_Polygon_crosses(self, (Polygon_t*)otherObject);

    case GEO_TYPE_POLYHEDRALSURFACE:
        return s_PolyhedralSurface_crosses(self, (PolyhedralSurface_t*)otherObject);

    case GEO_TYPE_ELLIPSE_EXTRUSION:
        return s_EllipseExtrusion_crosses(self, (EllipseExtrusion_t*)otherObject);

    case GEO_TYPE_SQUARE_EXTRUSION:
        return s_SquareExtrusion_crosses(self, (SquareExtrusion_t*)otherObject);

    case GEO_TYPE_POLYGON_EXTRUSION:
        return s_PolygonExtrusion_crosses(self, (PolygonExtrusion_t*)otherObject);

    case GEO_TYPE_POLYHEDRALSURFACE_EXTRUSION:
        return s_PolyhedralSurfaceExtrusion_crosses(self, (PolyhedralSurfaceExtrusion_t*)otherObject);

    default:
        return false;
    }
}

bool_t
PolygonExtrusion_within(PolygonExtrusion_t* self, Geometry_t* otherObject) {
    switch (otherObject->type) {
    case GEO_TYPE_POINT:
        return s_Point_within(self, (Point_t*)otherObject);

    case GEO_TYPE_LINESTRING:
        return s_LineString_within(self, (LineString_t*)otherObject);

    case GEO_TYPE_LINE:
        return s_Line_within(self, (Line_t*)otherObject);

    case GEO_TYPE_LINERING:
        return s_LineRing_within(self, (LineRing_t*)otherObject);

    case GEO_TYPE_ELLIPSE:
        return s_Ellipse_within(self, (Ellipse_t*)otherObject);

    case GEO_TYPE_SQUARE:
        return s_Square_within(self, (Square_t*)otherObject);

    case GEO_TYPE_POLYGON:
        return s_Polygon_within(self, (Polygon_t*)otherObject);

    case GEO_TYPE_POLYHEDRALSURFACE:
        return s_PolyhedralSurface_within(self, (PolyhedralSurface_t*)otherObject);

    case GEO_TYPE_ELLIPSE_EXTRUSION:
        return s_EllipseExtrusion_within(self, (EllipseExtrusion_t*)otherObject);

    case GEO_TYPE_SQUARE_EXTRUSION:
        return s_SquareExtrusion_within(self, (SquareExtrusion_t*)otherObject);

    case GEO_TYPE_POLYGON_EXTRUSION:
        return s_PolygonExtrusion_within(self, (PolygonExtrusion_t*)otherObject);

    case GEO_TYPE_POLYHEDRALSURFACE_EXTRUSION:
        return s_PolyhedralSurfaceExtrusion_within(self, (PolyhedralSurfaceExtrusion_t*)otherObject);

    default:
        return false;
    }
}

bool_t
PolygonExtrusion_contains(PolygonExtrusion_t* self, Geometry_t* otherObject) {
    switch (otherObject->type) {
    case GEO_TYPE_POINT:
        return s_Point_contains(self, (Point_t*)otherObject);

    case GEO_TYPE_LINESTRING:
        return s_LineString_contains(self, (LineString_t*)otherObject);

    case GEO_TYPE_LINE:
        return s_Line_contains(self, (Line_t*)otherObject);

    case GEO_TYPE_LINERING:
        return s_LineRing_contains(self, (LineRing_t*)otherObject);

    case GEO_TYPE_ELLIPSE:
        return s_Ellipse_contains(self, (Ellipse_t*)otherObject);

    case GEO_TYPE_SQUARE:
        return s_Square_contains(self, (Square_t*)otherObject);

    case GEO_TYPE_POLYGON:
        return s_Polygon_contains(self, (Polygon_t*)otherObject);

    case GEO_TYPE_POLYHEDRALSURFACE:
        return s_PolyhedralSurface_contains(self, (PolyhedralSurface_t*)otherObject);

    case GEO_TYPE_ELLIPSE_EXTRUSION:
        return s_EllipseExtrusion_contains(self, (EllipseExtrusion_t*)otherObject);

    case GEO_TYPE_SQUARE_EXTRUSION:
        return s_SquareExtrusion_contains(self, (SquareExtrusion_t*)otherObject);

    case GEO_TYPE_POLYGON_EXTRUSION:
        return s_PolygonExtrusion_contains(self, (PolygonExtrusion_t*)otherObject);

    case GEO_TYPE_POLYHEDRALSURFACE_EXTRUSION:
        return s_PolyhedralSurfaceExtrusion_contains(self, (PolyhedralSurfaceExtrusion_t*)otherObject);

    default:
        return false;
    }
}

bool_t
PolygonExtrusion_overlaps(PolygonExtrusion_t* self, Geometry_t* otherObject) {
    switch (otherObject->type) {
    case GEO_TYPE_POINT:
        return s_Point_overlaps(self, (Point_t*)otherObject);

    case GEO_TYPE_LINESTRING:
        return s_LineString_overlaps(self, (LineString_t*)otherObject);

    case GEO_TYPE_LINE:
        return s_Line_overlaps(self, (Line_t*)otherObject);

    case GEO_TYPE_LINERING:
        return s_LineRing_overlaps(self, (LineRing_t*)otherObject);

    case GEO_TYPE_ELLIPSE:
        return s_Ellipse_overlaps(self, (Ellipse_t*)otherObject);

    case GEO_TYPE_SQUARE:
        return s_Square_overlaps(self, (Square_t*)otherObject);

    case GEO_TYPE_POLYGON:
        return s_Polygon_overlaps(self, (Polygon_t*)otherObject);

    case GEO_TYPE_POLYHEDRALSURFACE:
        return s_PolyhedralSurface_overlaps(self, (PolyhedralSurface_t*)otherObject);

    case GEO_TYPE_ELLIPSE_EXTRUSION:
        return s_EllipseExtrusion_overlaps(self, (EllipseExtrusion_t*)otherObject);

    case GEO_TYPE_SQUARE_EXTRUSION:
        return s_SquareExtrusion_overlaps(self, (SquareExtrusion_t*)otherObject);

    case GEO_TYPE_POLYGON_EXTRUSION:
        return s_PolygonExtrusion_overlaps(self, (PolygonExtrusion_t*)otherObject);

    case GEO_TYPE_POLYHEDRALSURFACE_EXTRUSION:
        return s_PolyhedralSurfaceExtrusion_overlaps(self, (PolyhedralSurfaceExtrusion_t*)otherObject);

    default:
        return false;
    }
}


/******************************************************
 *          Static Functions Implementation
 ******************************************************/

static bool_t
s_Point_equals(PolygonExtrusion_t* self, Point_t* otherObject) {
    return false;
}

static bool_t
s_Point_disjoint(PolygonExtrusion_t* self, Point_t* otherObject) {
    return false;
}

static bool_t
s_Point_intersects(PolygonExtrusion_t* self, Point_t* otherObject) {
    return false;
}

static bool_t
s_Point_touches(PolygonExtrusion_t* self, Point_t* otherObject) {
    return false;
}

static bool_t
s_Point_crosses(PolygonExtrusion_t* self, Point_t* otherObject) {
    return false;
}

static bool_t
s_Point_within(PolygonExtrusion_t* self, Point_t* otherObject) {
    return false;
}

static bool_t
s_Point_contains(PolygonExtrusion_t* self, Point_t* otherObject) {
    return false;
}

static bool_t
s_Point_overlaps(PolygonExtrusion_t* self, Point_t* otherObject) {
    return false;
}

static bool_t
s_LineString_equals(PolygonExtrusion_t* self, LineString_t* otherObject) {
    return false;
}

static bool_t
s_LineString_disjoint(PolygonExtrusion_t* self, LineString_t* otherObject) {
    return false;
}

static bool_t
s_LineString_intersects(PolygonExtrusion_t* self, LineString_t* otherObject) {
    return false;
}

static bool_t
s_LineString_touches(PolygonExtrusion_t* self, LineString_t* otherObject) {
    return false;
}

static bool_t
s_LineString_crosses(PolygonExtrusion_t* self, LineString_t* otherObject) {
    return false;
}

static bool_t
s_LineString_within(PolygonExtrusion_t* self, LineString_t* otherObject) {
    return false;
}

static bool_t
s_LineString_contains(PolygonExtrusion_t* self, LineString_t* otherObject) {
    return false;
}

static bool_t
s_LineString_overlaps(PolygonExtrusion_t* self, LineString_t* otherObject) {
    return false;
}


static bool_t
s_Line_equals(PolygonExtrusion_t* self, Line_t* otherObject) {
    return false;
}

static bool_t
s_Line_disjoint(PolygonExtrusion_t* self, Line_t* otherObject) {
    return false;
}

static bool_t
s_Line_intersects(PolygonExtrusion_t* self, Line_t* otherObject) {
    return false;
}

static bool_t
s_Line_touches(PolygonExtrusion_t* self, Line_t* otherObject) {
    return false;
}

static bool_t
s_Line_crosses(PolygonExtrusion_t* self, Line_t* otherObject) {
    return false;
}

static bool_t
s_Line_within(PolygonExtrusion_t* self, Line_t* otherObject) {
    return false;
}

static bool_t
s_Line_contains(PolygonExtrusion_t* self, Line_t* otherObject) {
    return false;
}

static bool_t
s_Line_overlaps(PolygonExtrusion_t* self, Line_t* otherObject) {
    return false;
}


static bool_t
s_LineRing_equals(PolygonExtrusion_t* self, LineRing_t* otherObject) {
    return false;
}

static bool_t
s_LineRing_disjoint(PolygonExtrusion_t* self, LineRing_t* otherObject) {
    return false;
}

static bool_t
s_LineRing_intersects(PolygonExtrusion_t* self, LineRing_t* otherObject) {
    return false;
}

static bool_t
s_LineRing_touches(PolygonExtrusion_t* self, LineRing_t* otherObject) {
    return false;
}

static bool_t
s_LineRing_crosses(PolygonExtrusion_t* self, LineRing_t* otherObject) {
    return false;
}

static bool_t
s_LineRing_within(PolygonExtrusion_t* self, LineRing_t* otherObject) {
    return false;
}

static bool_t
s_LineRing_contains(PolygonExtrusion_t* self, LineRing_t* otherObject) {
    return false;
}

static bool_t
s_LineRing_overlaps(PolygonExtrusion_t* self, LineRing_t* otherObject) {
    return false;
}


static bool_t
s_Polygon_equals(PolygonExtrusion_t* self, Polygon_t* otherObject) {
    return false;
}

static bool_t
s_Polygon_disjoint(PolygonExtrusion_t* self, Polygon_t* otherObject) {
    return false;
}

static bool_t
s_Polygon_intersects(PolygonExtrusion_t* self, Polygon_t* otherObject) {
    return false;
}

static bool_t
s_Polygon_touches(PolygonExtrusion_t* self, Polygon_t* otherObject) {
    return false;
}

static bool_t
s_Polygon_crosses(PolygonExtrusion_t* self, Polygon_t* otherObject) {
    return false;
}

static bool_t
s_Polygon_within(PolygonExtrusion_t* self, Polygon_t* otherObject) {
    return false;
}

static bool_t
s_Polygon_contains(PolygonExtrusion_t* self, Polygon_t* otherObject) {
    return false;
}

static bool_t
s_Polygon_overlaps(PolygonExtrusion_t* self, Polygon_t* otherObject) {
    return false;
}


static bool_t
s_Ellipse_equals(PolygonExtrusion_t* self, Ellipse_t* otherObject) {
    return false;
}

static bool_t
s_Ellipse_disjoint(PolygonExtrusion_t* self, Ellipse_t* otherObject) {
    return false;
}

static bool_t
s_Ellipse_intersects(PolygonExtrusion_t* self, Ellipse_t* otherObject) {
    return false;
}

static bool_t
s_Ellipse_touches(PolygonExtrusion_t* self, Ellipse_t* otherObject) {
    return false;
}

static bool_t
s_Ellipse_crosses(PolygonExtrusion_t* self, Ellipse_t* otherObject) {
    return false;
}

static bool_t
s_Ellipse_within(PolygonExtrusion_t* self, Ellipse_t* otherObject) {
    return false;
}

static bool_t
s_Ellipse_contains(PolygonExtrusion_t* self, Ellipse_t* otherObject) {
    return false;
}

static bool_t
s_Ellipse_overlaps(PolygonExtrusion_t* self, Ellipse_t* otherObject) {
    return false;
}


static bool_t
s_Square_equals(PolygonExtrusion_t* self, Square_t* otherObject) {
    return false;
}

static bool_t
s_Square_disjoint(PolygonExtrusion_t* self, Square_t* otherObject) {
    return false;
}

static bool_t
s_Square_intersects(PolygonExtrusion_t* self, Square_t* otherObject) {
    return false;
}

static bool_t
s_Square_touches(PolygonExtrusion_t* self, Square_t* otherObject) {
    return false;
}

static bool_t
s_Square_crosses(PolygonExtrusion_t* self, Square_t* otherObject) {
    return false;
}

static bool_t
s_Square_within(PolygonExtrusion_t* self, Square_t* otherObject) {
    return false;
}

static bool_t
s_Square_contains(PolygonExtrusion_t* self, Square_t* otherObject) {
    return false;
}

static bool_t
s_Square_overlaps(PolygonExtrusion_t* self, Square_t* otherObject) {
    return false;
}


static bool_t
s_PolyhedralSurface_equals(PolygonExtrusion_t* self, PolyhedralSurface_t* otherObject) {
    return false;
}

static bool_t
s_PolyhedralSurface_disjoint(PolygonExtrusion_t* self, PolyhedralSurface_t* otherObject) {
    return false;
}

static bool_t
s_PolyhedralSurface_intersects(PolygonExtrusion_t* self, PolyhedralSurface_t* otherObject) {
    return false;
}

static bool_t
s_PolyhedralSurface_touches(PolygonExtrusion_t* self, PolyhedralSurface_t* otherObject) {
    return false;
}

static bool_t
s_PolyhedralSurface_crosses(PolygonExtrusion_t* self, PolyhedralSurface_t* otherObject) {
    return false;
}

static bool_t
s_PolyhedralSurface_within(PolygonExtrusion_t* self, PolyhedralSurface_t* otherObject) {
    return false;
}

static bool_t
s_PolyhedralSurface_contains(PolygonExtrusion_t* self, PolyhedralSurface_t* otherObject) {
    return false;
}

static bool_t
s_PolyhedralSurface_overlaps(PolygonExtrusion_t* self, PolyhedralSurface_t* otherObject) {
    return false;
}


static bool_t
s_EllipseExtrusion_equals(PolygonExtrusion_t* self, EllipseExtrusion_t* otherObject) {
    return false;
}

static bool_t
s_EllipseExtrusion_disjoint(PolygonExtrusion_t* self, EllipseExtrusion_t* otherObject) {
    return false;
}

static bool_t
s_EllipseExtrusion_intersects(PolygonExtrusion_t* self, EllipseExtrusion_t* otherObject) {
    return false;
}

static bool_t
s_EllipseExtrusion_touches(PolygonExtrusion_t* self, EllipseExtrusion_t* otherObject) {
    return false;
}

static bool_t
s_EllipseExtrusion_crosses(PolygonExtrusion_t* self, EllipseExtrusion_t* otherObject) {
    return false;
}

static bool_t
s_EllipseExtrusion_within(PolygonExtrusion_t* self, EllipseExtrusion_t* otherObject) {
    return false;
}

static bool_t
s_EllipseExtrusion_contains(PolygonExtrusion_t* self, EllipseExtrusion_t* otherObject) {
    return false;
}

static bool_t
s_EllipseExtrusion_overlaps(PolygonExtrusion_t* self, EllipseExtrusion_t* otherObject) {
    return false;
}


static bool_t
s_SquareExtrusion_equals(PolygonExtrusion_t* self, SquareExtrusion_t* otherObject) {
    return false;
}

static bool_t
s_SquareExtrusion_disjoint(PolygonExtrusion_t* self, SquareExtrusion_t* otherObject) {
    return false;
}

static bool_t
s_SquareExtrusion_intersects(PolygonExtrusion_t* self, SquareExtrusion_t* otherObject) {
    return false;
}

static bool_t
s_SquareExtrusion_touches(PolygonExtrusion_t* self, SquareExtrusion_t* otherObject) {
    return false;
}

static bool_t
s_SquareExtrusion_crosses(PolygonExtrusion_t* self, SquareExtrusion_t* otherObject) {
    return false;
}

static bool_t
s_SquareExtrusion_within(PolygonExtrusion_t* self, SquareExtrusion_t* otherObject) {
    return false;
}

static bool_t
s_SquareExtrusion_contains(PolygonExtrusion_t* self, SquareExtrusion_t* otherObject) {
    return false;
}

static bool_t
s_SquareExtrusion_overlaps(PolygonExtrusion_t* self, SquareExtrusion_t* otherObject) {
    return false;
}


static bool_t
s_PolygonExtrusion_equals(PolygonExtrusion_t* self, PolygonExtrusion_t* otherObject) {
    return false;
}

static bool_t
s_PolygonExtrusion_disjoint(PolygonExtrusion_t* self, PolygonExtrusion_t* otherObject) {
    return false;
}

static bool_t
s_PolygonExtrusion_intersects(PolygonExtrusion_t* self, PolygonExtrusion_t* otherObject) {
    return false;
}

static bool_t
s_PolygonExtrusion_touches(PolygonExtrusion_t* self, PolygonExtrusion_t* otherObject) {
    return false;
}

static bool_t
s_PolygonExtrusion_crosses(PolygonExtrusion_t* self, PolygonExtrusion_t* otherObject) {
    return false;
}

static bool_t
s_PolygonExtrusion_within(PolygonExtrusion_t* self, PolygonExtrusion_t* otherObject) {
    return false;
}

static bool_t
s_PolygonExtrusion_contains(PolygonExtrusion_t* self, PolygonExtrusion_t* otherObject) {
    return false;
}

static bool_t
s_PolygonExtrusion_overlaps(PolygonExtrusion_t* self, PolygonExtrusion_t* otherObject) {
    return false;
}


static bool_t
s_PolyhedralSurfaceExtrusion_equals(PolygonExtrusion_t* self, PolyhedralSurfaceExtrusion_t* otherObject) {
    return false;
}

static bool_t
s_PolyhedralSurfaceExtrusion_disjoint(PolygonExtrusion_t* self, PolyhedralSurfaceExtrusion_t* otherObject) {
    return false;
}

static bool_t
s_PolyhedralSurfaceExtrusion_intersects(PolygonExtrusion_t* self, PolyhedralSurfaceExtrusion_t* otherObject) {
    return false;
}

static bool_t
s_PolyhedralSurfaceExtrusion_touches(PolygonExtrusion_t* self, PolyhedralSurfaceExtrusion_t* otherObject) {
    return false;
}

static bool_t
s_PolyhedralSurfaceExtrusion_crosses(PolygonExtrusion_t* self, PolyhedralSurfaceExtrusion_t* otherObject) {
    return false;
}

static bool_t
s_PolyhedralSurfaceExtrusion_within(PolygonExtrusion_t* self, PolyhedralSurfaceExtrusion_t* otherObject) {
    return false;
}

static bool_t
s_PolyhedralSurfaceExtrusion_contains(PolygonExtrusion_t* self, PolyhedralSurfaceExtrusion_t* otherObject) {
    return false;
}

static bool_t
s_PolyhedralSurfaceExtrusion_overlaps(PolygonExtrusion_t* self, PolyhedralSurfaceExtrusion_t* otherObject) {
    return false;
}

#endif
