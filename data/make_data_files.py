#!/usr/bin/env python3

##
#  Retrieves the actual data files from hypocenter. They are
#  very big
#

import getopt
import sys
import subprocess

if sys.version_info.major >= (3) :
  from urllib.request import urlopen
else:
  from urllib2 import urlopen

model = "CVMSI"

def usage():
    print("\n./make_data_files.py\n\n")
    sys.exit(0)

def download_urlfile(url,fname):
#  print(" >>> grabbing (%s) %s\n",fname,url);
  try:
    response = urlopen(url)
    CHUNK = 16 * 1024
    with open(fname, 'wb') as f:
      while True:
        chunk = response.read(CHUNK)
        if not chunk:
          break
        f.write(chunk)
  except:
    e = sys.exc_info()[0]
    print("Exception retrieving and saving model datafiles:",e)
    raise
  return True

def main():

    # Set our variable defaults.
    path = ""
    mdir = ""

    print("\nDownloading model dataset\n")

    ## look for model_data_path and other varaibles
    try:
        fp = open('./config','r')
    except:
        print("ERROR: failed to open config file")
        sys.exit(1)

    lines = fp.readlines()
    for line in lines :
        if line[0] == '#' :
          continue
        parts = line.split('=')
        if len(parts) < 2 :
          continue;
        variable=parts[0].strip()
        val=parts[1].strip()

        if (variable == 'model_download_data_path') :
            path = val + '/' + model
            continue
        if (variable == 'model_download_dir') :
            mdir = val
            continue
        continue
    if path == "" :
        print("ERROR: failed to find variables in config file")
        sys.exit(1)
    fp.close()

    subprocess.check_call(["mkdir", "-p", "i26"])
    flist=['box.dat', 'cvmsi.bin', 'cvmsi.ver', 'region_spec.in', 'XYZGRD']
    for f in flist :
        fname = "i26/" +f
        url = path + "/" + mdir + "/i26/" + f
        download_urlfile(url,fname)

    subprocess.check_call(["mkdir", "-p", "cvms"])

    fflist=['3D.out', 'b1___edge', 'b1___sur2', 'b2___edge', 'b2___sur2', 'b3___edge', 'b3___sur2', 'b4___edge', 'b4___sur2', 'b5___edge', 'b5___sur2', 'bmod_edge', 'borehole.h', 'boreholes', 'cvms.h', 'cvms_sub.f', 'dim2.h', 'dim8.h', 'eh.modPS', 'genprod.h', 'genpro.h', 'impva.edge', 'in.h', 'innum.h', 'ivmod.edge', 'ivsurfaced.h', 'ivsurface.h', 'ku1__edge', 'ku1__sur2', 'ku2__edge', 'ku2__sur2', 'ku3__edge', 'ku3__sur2', 'ku4__edge', 'ku4__sur2', 'ku5__edge', 'ku5__sur2', 'ku8__edge', 'ku8__sur2', 'laba_edge', 'laba_sur2', 'lab_geo2_geology', 'labup.h', 'lamo_edge', 'lamo_sur2', 'lare_edge', 'lare_sur2', 'laup_edge', 'laup_sur2', 'Makefile.am', 'mantled.h', 'mantle.h', 'moho1.h', 'moho_sur', 'names.h', 'nsbb_edge', 'nsbb_sur2', 'params.h', 'pu1__edge', 'pu1__sur2', 'pu2A_edge', 'pu2A_sur2', 'pu2B_edge', 'pu2B_sur2', 'pu3__edge', 'pu3__sur2', 'pu9__edge', 'pu9__sur2', 'q12b_edge', 'q12b_sur2', 'q12x_edge', 'q12x_sur2', 'q12y_edge', 'q12y_sur2', 'q12z_edge', 'q12z_sur2', 'qps1_edge', 'qps1_sur2', 'qps2_edge', 'qps2_sur2', 'qps5_edge', 'qps5_sur2', 'qps6_edge', 'qps6_sur2', 'regionald.h', 'regional.h', 'salton_base.sur', 'sbb2_edge', 'sbb2_sur2', 'sbb__edge', 'sbb__sur2', 'sbmi_edge', 'sbmi_sur2', 'sbmo_edge', 'sbmo_sur2', 'sgba_edge', 'sgba_sur2', 'sgeod.h', 'sgeo.h', 'sgmo_edge', 'sgmo_sur2', 'sgre_edge', 'sgre_sur2', 'sku2_edge', 'sku2_sur2', 'smb1_edge', 'smb2_edge', 'smb2_sur2', 'smb3_edge', 'smb3_sur2', 'smb9_edge', 'smb9_sur2', 'smm1_edge', 'smm1_sur2', 'smm2_edge', 'smm2_sur2', 'smr1_edge', 'smr1_sur2', 'smr2_edge', 'smr2_sur2', 'soil1.h', 'soil_generic', 'soil.pgm', 'sp9b_edge', 'sp9b_sur2', 'spu1_edge', 'spu1_sur2', 'spu9_edge', 'spu9_sur2', 'st4b_edge', 'st4b_sur2', 'st4s_edge', 'st4s_sur2', 'ste2_edge', 'ste2_sur2', 'surfaced.h', 'surface.h', 'te1__edge', 'te1__sur2', 'te2__edge', 'te2__sur2', 'te3__edge', 'te3__sur2', 'te4__edge', 'te4__sur2', 'te5__edge', 'te5__sur2', 'te6A_edge', 'te6A_sur2', 'te6B_edge', 'te6B_sur2', 'te7__edge', 'te7__sur2', 'te8__edge', 'te8__sur2', 'tj1__edge', 'tj1__sur2', 'tj2__edge', 'tj2__sur2', 'tj3__edge', 'tj3__sur2', 'tj4__edge', 'tj4__sur2', 'tj5__edge', 'tj5__sur2', 'tsq1_edge', 'tsq1_sur2', 'tsq2_edge', 'tsq2_sur2', 'tsq3_edge', 'tsq3_sur2', 'tsq4_edge', 'tsq4_sur2', 'tsq5_edge', 'tsq5_sur2', 'tsq7_edge', 'tsq7_sur2', 'tsq9_edge', 'tsq9_sur2', 'tv1__edge', 'tv1__sur2', 'tv2__edge', 'tv2__sur2', 'tv3__edge', 'tv3__sur2', 'tv5__edge', 'tv5__sur2', 'tv9__edge', 'tv9__sur2', 'version.h', 'wtbh1d.h', 'wtbh1.h', 'wtbh2.h', 'wtbh3.h']

    for ff in fflist :
        fname = "cvms/"+ff
        url = path + "/" + mdir + "/cvms/" + ff
        download_urlfile(url,fname)

    print("\nDone!")

if __name__ == "__main__":
    main()
