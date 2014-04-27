dir_lib = 'd:\projects\hpgc_prj\hpgc\Debug'
dir_include = 'src'
pub_dir = "c:/hpgc_runtime"

include_file = FileList.new("#{dir_include}/mpiobject/*.h","#{dir_include}/geoformat/*.h")
lib_file = FileList.new("#{dir_lib}/mpiobject.lib","#{dir_lib}/geoformat.lib")
pub_file= FileList.new("#{pub_dir}/include/*.h","#{pub_dir}/lib")

desc "publish"
task :publish do 
    rm_f pub_file
    cp include_file,"#{pub_dir}/include"
    cp lib_file,"#{pub_dir}/lib"
end

desc "test"
task :test do
    num = (ENV['n'] ? ENV('n') : '2').to_i
    sh "mpiexec -n #{num} #{dir_lib}/hpgc.exe"
end

task :default => :test 