#include "PCL.h"

void PCL::ComputePlaneNormalByPCA(QList<QVector3D> plist, QVector3D & position, QVector3D & halfExtents, QVector3D * eVectors){
	if (plist.size() == 0)		
		return;

	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>());
	for each (QVector3D var in plist)
		cloud->push_back(PointT(var[0], var[1], var[2]));

	Eigen::Matrix3f eigenVectorsPCA;
	Eigen::Vector3f eigenValuesPCA;
									  
	Eigen::Vector4f pcaCentroid;
	pcl::compute3DCentroid(*cloud, pcaCentroid);
	Eigen::Matrix3f covariance;
	pcl::computeCovarianceMatrixNormalized(*cloud, pcaCentroid, covariance);
	Eigen::SelfAdjointEigenSolver<Eigen::Matrix3f> eigen_solver(covariance, Eigen::ComputeEigenvectors);
	eigenVectorsPCA = eigen_solver.eigenvectors();
	eigenValuesPCA = eigen_solver.eigenvalues();
												
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloudPCAprojection(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PCA<pcl::PointXYZ> pca;
	pca.setInputCloud(cloud);
	pca.project(*cloud, *cloudPCAprojection);
	eigenVectorsPCA = pca.getEigenVectors();
	eigenValuesPCA = pca.getEigenValues();

	eigenVectorsPCA.col(2) = eigenVectorsPCA.col(0).cross(eigenVectorsPCA.col(1)); 
	eigenVectorsPCA.col(0) = eigenVectorsPCA.col(1).cross(eigenVectorsPCA.col(2));
	eigenVectorsPCA.col(1) = eigenVectorsPCA.col(2).cross(eigenVectorsPCA.col(0));

	Eigen::Matrix4f tm = Eigen::Matrix4f::Identity();
	Eigen::Matrix4f tm_inv = Eigen::Matrix4f::Identity();
	tm.block<3, 3>(0, 0) = eigenVectorsPCA.transpose();   
	tm.block<3, 1>(0, 3) = -1.0f * (eigenVectorsPCA.transpose()) *(pcaCentroid.head<3>());
	tm_inv = tm.inverse();

	pcl::PointCloud<PointT>::Ptr transformedCloud(new pcl::PointCloud<PointT>);
	pcl::transformPointCloud(*cloud, *transformedCloud, tm);

	PointT min_p1, max_p1;
	Eigen::Vector3f c1, c;
	pcl::getMinMax3D(*transformedCloud, min_p1, max_p1);
	c1 = 0.5f*(min_p1.getVector3fMap() + max_p1.getVector3fMap());

	Eigen::Affine3f tm_inv_aff(tm_inv);
	pcl::transformPoint(c1, c, tm_inv_aff);

	Eigen::Vector3f whd, whd1;
	whd1 = max_p1.getVector3fMap() - min_p1.getVector3fMap();
	whd = whd1;
	float sc1 = (whd1(0) + whd1(1) + whd1(2)) / 3;  

	position = QVector3D(c1[0], c1[1], c1[2]);
	position = QVector3D(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < plist.size(); i++)
		position += plist[i];
	position /= (double)plist.size();

	eVectors[0] = QVector3D(eigenVectorsPCA.col(0)[0], eigenVectorsPCA.col(0)[1], eigenVectorsPCA.col(0)[2]);
	eVectors[1] = QVector3D(eigenVectorsPCA.col(1)[0], eigenVectorsPCA.col(1)[1], eigenVectorsPCA.col(1)[2]);
	eVectors[2] = QVector3D(eigenVectorsPCA.col(2)[0], eigenVectorsPCA.col(2)[1], eigenVectorsPCA.col(2)[2]);
	halfExtents = QVector3D(whd1(0), whd1(1), whd1(2));

	QList<QVector3D> length;
	QList<QVector3D> poss;
	QList<QVector3D*>vectors;

	for (int i = 0; i < 6; i++)	{
		QVector3D pos = position;
		QVector3D* vv = new QVector3D[3];
		QVector3D len;
		if (i == 0)	{
			vv[0] = eVectors[0];
			vv[1] = eVectors[1];
			vv[2] = eVectors[2];
		}
		if (i == 1)	{
			vv[0] = eVectors[1];
			vv[1] = eVectors[0];
			vv[2] = eVectors[2];
		}
		if (i == 2)	{
			vv[0] = eVectors[0];
			vv[1] = eVectors[2];
			vv[2] = eVectors[1];
		}
		if (i == 3)	{
			vv[0] = eVectors[2];
			vv[1] = eVectors[0];
			vv[2] = eVectors[1];
		}
		if (i == 4)	{
			vv[0] = eVectors[2];
			vv[1] = eVectors[1];
			vv[2] = eVectors[0];
		}
		if (i == 5)	{
			vv[0] = eVectors[1];
			vv[1] = eVectors[2];
			vv[2] = eVectors[0];
		}
		BasicFun::schmidtOrthogonal(vv[0], vv[1], vv[2]);
		BasicFun::VomputeLenth(pos, plist, vv, len);

		length.append(len);
		vectors.append(vv);
		poss.append(pos);
	}
	halfExtents = QVector3D(0, 0, 0);
	for (int i = 0; i < vectors.size(); i++)	{
		if (halfExtents == QVector3D(0, 0, 0))		{
			halfExtents = length[i];
			position = poss[i];
			for (int j = 0; j < 3; j++)
				eVectors[j] = vectors[i][j];
		}
		else		{
			double minlt = Bvector(halfExtents).getMinXYZ();
			double minlo = Bvector(length[i]).getMinXYZ();

			if (minlt > minlo)			{
				halfExtents = length[i];
				position = poss[i];
				for (int j = 0; j < 3; j++)
					eVectors[j] = vectors[i][j];
			}
		}
	}
}
