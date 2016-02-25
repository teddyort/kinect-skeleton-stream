using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Forms;
using Microsoft.Kinect;
using Microsoft.Kinect.Toolkit;

namespace SkeletonStream
{
    public partial class frmMain : Form
    {
        private KinectSensorChooser _chooser;
        private Bitmap _bitmap;
        private KinectSensor _sensor;

        public frmMain()
        {
            InitializeComponent();
        }

        private void frmMain_Load(object sender, EventArgs e)
        {
            _chooser = new KinectSensorChooser();
            _chooser.KinectChanged += ChooserSensorChanged;
            _chooser.Start();
        }

        void ChooserSensorChanged(object sender, KinectChangedEventArgs e)
        {
            var old = e.OldSensor; 
            StopKinect(old); 
 
            _sensor = e.NewSensor; 
            if (_sensor == null) 
            { 
                return; 
            }

            if (chkSeatedMode.Checked)
            {
                _sensor.SkeletonStream.TrackingMode = SkeletonTrackingMode.Seated;
            }

            _sensor.SkeletonStream.Enable();
            _sensor.SkeletonFrameReady += SkeletonFrameReady;
 
            try 
            { 
                _sensor.Start(); 
                lblStatus.Text = "Kinect Started" + "\r"; 
            } 
            catch (System.IO.IOException) 
            {
                lblStatus.Text = "Kinect Not Started" + "\r"; 
                //maybe another app is using Kinect 
                _chooser.TryResolveConflict(); 
            } 
        } 
 
        private void StopKinect(KinectSensor sensor) 
        { 
            if (sensor != null) 
            { 
                if (sensor.IsRunning) 
                { 
                    sensor.Stop(); 
                    sensor.AudioSource.Stop(); 
                } 
            } 
        }

        void SkeletonFrameReady(object sender, SkeletonFrameReadyEventArgs e)
        {
            Skeleton[] skeletons = new Skeleton[0];

            using (SkeletonFrame skeletonFrame = e.OpenSkeletonFrame())
            {
                if (skeletonFrame != null)
                {
                    skeletons = new Skeleton[skeletonFrame.SkeletonArrayLength];
                    skeletonFrame.CopySkeletonDataTo(skeletons);
                }
            }

            if (skeletons.Length != 0)
            {
                foreach (Skeleton skel in skeletons)
                {
                    if (skel.TrackingState == SkeletonTrackingState.Tracked)
                    {
                        this.OutputBonesAndJoints(skel);
                    }
                }
            }
        }

        void OutputBonesAndJoints(Skeleton skel)
        {
            dgvTable.Rows.Clear();
            foreach (BoneOrientation bone in skel.BoneOrientations)
            {
                dgvTable.Rows.Add(new object[] {bone.EndJoint.ToString(), Vector4ToString(bone.AbsoluteRotation.Quaternion)});
            }
        }

        String Vector4ToString(Vector4 vec)
        {
            return "(" + vec.X + ", " + vec.Y + ", " + vec.Z + ", " + vec.W + ")";
        }

        private void chkSeatedMode_CheckedChanged(object sender, EventArgs e)
        {
            if (null != this._sensor)
            {
                if (this.chkSeatedMode.Checked)
                {
                    this._sensor.SkeletonStream.TrackingMode = SkeletonTrackingMode.Seated;
                }
                else
                {
                    this._sensor.SkeletonStream.TrackingMode = SkeletonTrackingMode.Default;
                }
            }
        }
    }
}
