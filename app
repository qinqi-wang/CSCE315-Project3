apply plugin: 'com.android.model.application'
model {
    android {
        compileSdkVersion 24
        buildToolsVersion "24.0.0"

        defaultConfig {
            applicationId "com.example.ray.a5tac2"
            minSdkVersion.apiLevel 15
            targetSdkVersion.apiLevel 24
            versionCode 1
            versionName "1.0"

            buildConfigFields {
                create() {
                    type "int"
                    name "VALUE"
                    value "1"
                }
            }
        }
        buildTypes {
            release {
                minifyEnabled false
                proguardFiles.add(file('proguard-android.txt'))
            }
        }
        ndk {
            moduleName "hello-android-jni"
            stl "gnustl_shared"
        }
        productFlavors {
            create("flavor1") {
                applicationId "com.app"
            }
        }

    }
}

    dependencies {
        compile fileTree(dir: 'libs', include: ['*.jar'])
        testCompile 'junit:junit:4.12'
        compile 'com.android.support:appcompat-v7:24.0.0'
    }
