/*
 * Copyright (c) 2008, AIST, the University of Tokyo and General Robotix Inc.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */

/** \file
    \brief The header file of the LinkPath and JointPath classes
    \author Shin'ichiro Nakaoka
*/

#ifndef OPENHRP_LINK_PATH_H_INCLUDED
#define OPENHRP_LINK_PATH_H_INCLUDED

#include <vector>
#include <ostream>
#include <boost/shared_ptr.hpp>
#include <hrpUtil/Tvmet3d.h>
#include "uBlasCommonTypes.h"
#include "LinkTraverse.h"
#include "exportdef.h"


namespace hrp {

	class HRPMODEL_API LinkPath : public LinkTraverse
	{
	public:
		LinkPath();
		LinkPath(Link* root, Link* end);
		/// set path from the root link
		LinkPath(Link* end);
		
		/**
		   true when the path is not empty
		*/
		inline operator bool() const {
			return !links.empty();
		}

		inline Link* endLink() const {
			return links.back();
		}
		
		bool find(Link* root, Link* end);
		void findPathFromRoot(Link* end);
		
	private:
		bool findPathSub(Link* link, Link* prev, Link* end, bool isForwardDirection);
		void findPathFromRootSub(Link* link);
	};


	class HRPMODEL_API JointPath : public LinkPath
    {
    public:
		
		JointPath();
		JointPath(Link* root, Link* end);
		/// set path from the root link
		JointPath(Link* end);
		virtual ~JointPath();
		
		bool find(Link* root, Link* end);
		bool findPathFromRoot(Link* end);
		
		inline int numJoints() const {
			return joints.size();
		}
		
		inline Link* joint(int index) const {
			return joints[index];
		}

		inline Link* endJoint() const {
			return joints.back();
		}
		
		inline bool isJointDownward(int index) const {
			return (index >= numUpwardJointConnections);
		}
		
		void calcJacobian(dmatrix& out_J) const;
		
		inline dmatrix Jacobian() const {
			dmatrix J;
			calcJacobian(J);
			return J;
		}

		// InverseKinematics Interface
		virtual void setMaxIKError(double e);
		virtual void setBestEffortIKMode(bool on);
		virtual bool calcInverseKinematics(const Vector3& end_p, const Matrix33& end_R);
		virtual bool hasAnalyticalIK();

		bool calcInverseKinematics(
			const Vector3& base_p, const Matrix33& base_R, const Vector3& end_p, const Matrix33& end_R);
		
		/**
		   @deprecated use operator<<
		*/
		void putInformation(std::ostream& os) const;
		
    protected:
		
		virtual void onJointPathUpdated();
		
		double maxIKErrorSqr;
		bool isBestEffortIKMode;
		
    private:
		
		void initialize();
		void extractJoints();
		
		std::vector<Link*> joints;
		int numUpwardJointConnections;
    };

	typedef boost::shared_ptr<JointPath> JointPathPtr;
	
};


HRPMODEL_API std::ostream& operator<<(std::ostream& os, hrp::LinkTraverse& traverse);


#endif