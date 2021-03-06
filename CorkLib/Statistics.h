// +-------------------------------------------------------------------------
// | Statistics.h
// | 
// | Author: Stephan Friedl
// +-------------------------------------------------------------------------
// | COPYRIGHT:
// |    Copyright Stephan Friedl 2015
// |    See the included COPYRIGHT file for further details.
// |    
// |    This file is part of the Cork library.
// |
// |    Cork is free software: you can redistribute it and/or modify
// |    it under the terms of the GNU Lesser General Public License as
// |    published by the Free Software Foundation, either version 3 of
// |    the License, or (at your option) any later version.
// |
// |    Cork is distributed in the hope that it will be useful,
// |    but WITHOUT ANY WARRANTY; without even the implied warranty of
// |    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// |    GNU Lesser General Public License for more details.
// |
// |    You should have received a copy 
// |    of the GNU Lesser General Public License
// |    along with Cork.  If not, see <http://www.gnu.org/licenses/>.
// +-------------------------------------------------------------------------


#pragma once


#include <memory>

#include "Math\Primitives.h"
#include "Util\AlignedUniquePtr.h"



namespace Cork
{
	namespace Statistics
	{


		class GeometricStatistics
		{
		public :
	
			GeometricStatistics( size_t							numVertices,
								 size_t							numTriangles,
								 double							area,
								 double							volume,
								 double							minEdgeLength,
								 double							maxEdgeLength,
								 const Cork::Math::BBox3D&		boundingBox )
				: m_numVertices( numVertices ),
				  m_numTriangles( numTriangles ),
				  m_area( area ),
				  m_volume( volume),
				  m_minEdgeLength( minEdgeLength ),
				  m_maxEdgeLength( maxEdgeLength ),
				  m_boundingBox( make_aligned<Cork::Math::BBox3D>( boundingBox ))
			{}



			size_t				numVertices() const
			{
				return( m_numVertices );
			}

			size_t				numTriangles() const
			{
				return( m_numTriangles );
			}

			Cork::Math::BBox3D	boundingBox() const
			{
				return( *m_boundingBox );
			}

			double				area() const
			{
				return( m_area );
			}

			double				volume() const
			{
				return( m_volume );
			}

			double				minEdgeLength() const
			{
				return( m_minEdgeLength );
			}

			double				maxEdgeLength() const
			{
				return( m_maxEdgeLength );
			}


		private :

			size_t										m_numVertices;
			size_t										m_numTriangles;
			double										m_area;
			double										m_volume;
			double										m_minEdgeLength;
			double										m_maxEdgeLength;
			aligned_unique_ptr<Cork::Math::BBox3D>		m_boundingBox; 
		};



					
		class TopologicalStatistics
		{
		public :

			typedef std::vector<Cork::Math::EdgeBase>			EdgeVector;



			TopologicalStatistics( size_t							numEdges,
								   size_t							numBodies,
								   std::unique_ptr<EdgeVector>&		nonTwoManifoldEdges )
				: m_numEdges( numEdges ),
				  m_numBodies( numBodies ),
				  m_nonTwoManifoldEdges( std::move( nonTwoManifoldEdges ))
			{}

			TopologicalStatistics( TopologicalStatistics&&			statsToMove )
				: m_numEdges( statsToMove.m_numEdges ),
				  m_numBodies( statsToMove.m_numBodies ),
				  m_nonTwoManifoldEdges( std::move( statsToMove.m_nonTwoManifoldEdges ))
			{}



			size_t										numEdges() const
			{
				return( m_numEdges );
			}

			size_t										numBodies() const
			{
				return( m_numBodies );
			}

			bool										IsTwoManifold() const
			{
				return( m_nonTwoManifoldEdges->empty() );
			}

			EdgeVector&									NonTwoManifoldEdges() const
			{
				return( *m_nonTwoManifoldEdges );
			}

		private :

			size_t							m_numEdges;
			size_t							m_numBodies;

			std::unique_ptr<EdgeVector>		m_nonTwoManifoldEdges;
		};


	}
}
 