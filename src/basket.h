#ifndef __BASKET_H__
#define __BASKET_H__

#include <GL/glew.h>

#include "types.h"
#include "entity.h"
#include "mesh.h"
#include "meshregistry.h"

static const Vertex basketVertices[] = {
    {{-0.889787f, -0.230558f, -0.155609f,  1.000000f}, {-0.871100f, -0.469600f, -0.143700f}},
    {{-0.785733f, -0.368716f,  0.141880f,  1.000000f}, {-0.731900f, -0.670800f,  0.120000f}},
    {{-0.920202f, -0.137804f,  0.181512f,  1.000000f}, {-0.900400f, -0.394700f,  0.183100f}},
    {{ 0.625908f, -0.340780f,  0.549165f,  1.000000f}, { 0.587400f, -0.628500f,  0.509800f}},
    {{ 0.870837f, -0.203529f,  0.296793f,  1.000000f}, { 0.851700f, -0.456000f,  0.258300f}},
    {{ 0.639558f, -0.137762f,  0.697374f,  1.000000f}, { 0.652000f, -0.334900f,  0.680300f}},
    {{-0.189338f, -0.340685f,  0.818702f,  1.000000f}, {-0.205000f, -0.625600f,  0.752800f}},
    {{-0.004019f, -0.174708f,  0.947306f,  1.000000f}, {-0.002900f, -0.405500f,  0.914100f}},
    {{-0.453827f, -0.137805f,  0.834617f,  1.000000f}, {-0.468900f, -0.377600f,  0.798500f}},
    {{-0.189337f, -0.340683f, -0.818704f,  1.000000f}, {-0.208100f, -0.626800f, -0.750900f}},
    {{-0.453827f, -0.137804f, -0.834618f,  1.000000f}, {-0.468900f, -0.377600f, -0.798500f}},
    {{-0.004017f, -0.174705f, -0.947307f,  1.000000f}, {-0.004800f, -0.385500f, -0.922700f}},
    {{ 0.625907f, -0.340777f, -0.549169f,  1.000000f}, { 0.600900f, -0.626600f, -0.496300f}},
    {{ 0.639559f, -0.137758f, -0.697375f,  1.000000f}, { 0.653300f, -0.350400f, -0.671100f}},
    {{ 0.883998f, -0.174803f, -0.296790f,  1.000000f}, { 0.878100f, -0.397400f, -0.266700f}},
    {{ 0.876366f,  0.023112f, -0.466955f,  1.000000f}, { 0.885800f,  0.057500f, -0.460400f}},
    {{ 0.790522f,  0.156418f, -0.494874f,  1.000000f}, { 0.694700f,  0.541400f, -0.473600f}},
    {{ 0.916945f,  0.155563f, -0.111606f,  1.000000f}, { 0.858900f,  0.501800f, -0.102600f}},
    {{ 0.742828f,  0.271685f, -0.342556f,  1.000000f}, {-0.427400f,  0.842100f,  0.328800f}},
    {{ 0.477533f,  0.269933f, -0.675441f,  1.000000f}, {-0.510000f,  0.829300f,  0.228500f}},
    {{ 0.483114f,  0.155065f, -0.810078f,  1.000000f}, { 0.433800f,  0.531000f, -0.727900f}},
    {{ 0.580994f,  0.022551f, -0.798066f,  1.000000f}, { 0.629900f,  0.067000f, -0.773800f}},
    {{-0.439243f,  0.023104f, -0.901975f,  1.000000f}, {-0.446300f,  0.038600f, -0.894100f}},
    {{-0.029101f,  0.075071f, -0.989771f,  1.000000f}, {-0.027000f,  0.243900f, -0.969400f}},
    {{-0.188277f,  0.273520f, -0.797341f,  1.000000f}, {-0.538100f,  0.663100f,  0.520400f}},
    {{ 0.040944f,  0.295164f, -0.826136f,  1.000000f}, { 0.072700f,  0.524600f, -0.848200f}},
    {{-0.457007f,  0.156531f, -0.830159f,  1.000000f}, {-0.447300f,  0.538900f, -0.713800f}},
    {{-0.432120f,  0.271526f, -0.701297f,  1.000000f}, { 0.335300f,  0.815600f,  0.471600f}},
    {{-0.806200f,  0.155543f, -0.458350f,  1.000000f}, {-0.725200f,  0.539500f, -0.427800f}},
    {{-0.805528f,  0.275575f, -0.104151f,  1.000000f}, { 0.550400f,  0.832800f,  0.058900f}},
    {{-0.712893f,  0.266835f, -0.403288f,  1.000000f}, { 0.506200f,  0.833900f,  0.219800f}},
    {{-0.930994f,  0.022556f, -0.298061f,  1.000000f}, {-0.956100f,  0.058400f, -0.287000f}},
    {{-0.925333f,  0.156475f, -0.072565f,  1.000000f}, {-0.857300f,  0.508200f, -0.081900f}},
    {{-0.978636f,  0.023097f,  0.146905f,  1.000000f}, {-0.988000f,  0.063900f,  0.140600f}},
    {{-0.788680f,  0.271829f,  0.206658f,  1.000000f}, { 0.561700f,  0.826900f, -0.028100f}},
    {{-0.891972f,  0.153571f,  0.257588f,  1.000000f}, {-0.807200f,  0.521000f,  0.277400f}},
    {{-0.677121f,  0.155578f,  0.638986f,  1.000000f}, {-0.632000f,  0.511600f,  0.582100f}},
    {{-0.399502f,  0.272306f,  0.717841f,  1.000000f}, { 0.130200f,  0.811100f, -0.570300f}},
    {{-0.616842f,  0.269745f,  0.543266f,  1.000000f}, { 0.425000f,  0.834500f, -0.350600f}},
    {{-0.439244f,  0.023104f,  0.901974f,  1.000000f}, {-0.450700f,  0.057800f,  0.890800f}},
    {{-0.352016f,  0.157899f,  0.873201f,  1.000000f}, {-0.296400f,  0.530700f,  0.794100f}},
    {{-0.186281f,  0.274110f,  0.806970f,  1.000000f}, {-0.006300f,  0.553300f,  0.833000f}},
    {{ 0.077138f,  0.149217f,  0.947461f,  1.000000f}, { 0.088300f,  0.507100f,  0.857300f}},
    {{-0.056060f,  0.266118f,  0.827534f,  1.000000f}, {-0.025600f,  0.377800f,  0.925500f}},
    {{-0.009211f,  0.022564f,  0.993172f,  1.000000f}, {-0.053400f,  0.082700f,  0.995100f}},
    {{ 0.065997f,  0.260735f,  0.827504f,  1.000000f}, { 0.027900f,  0.412300f,  0.910600f}},
    {{ 0.876367f,  0.023110f,  0.466954f,  1.000000f}, { 0.878400f,  0.036900f,  0.476500f}},
    {{ 0.594970f,  0.073997f,  0.783793f,  1.000000f}, { 0.592600f,  0.259300f,  0.762600f}},
    {{ 0.849188f,  0.156560f,  0.398315f,  1.000000f}, { 0.771100f,  0.543900f,  0.331100f}},
    {{ 0.473260f,  0.270754f,  0.679489f,  1.000000f}, {-0.282200f,  0.896300f, -0.342100f}},
    {{ 0.742576f,  0.271711f,  0.346733f,  1.000000f}, {-0.465500f,  0.827200f, -0.314600f}},
    {{ 0.172660f,  0.269027f, -0.802063f,  1.000000f}, { 0.793300f,  0.443300f,  0.417300f}},
    {{ 0.346624f,  0.001532f, -0.933423f,  1.000000f}, { 0.327900f,  0.023700f, -0.944400f}},
    {{ 0.382986f, -0.263312f, -0.802303f,  1.000000f}, { 0.378500f, -0.532400f, -0.757200f}},
    {{ 0.187991f, -0.394974f, -0.764035f,  1.000000f}, { 0.178100f, -0.730300f, -0.659600f}},
    {{-0.819522f,  0.001535f, -0.547875f,  1.000000f}, {-0.817400f,  0.000400f, -0.576100f}},
    {{-0.599048f, -0.277577f, -0.649332f,  1.000000f}, {-0.570800f, -0.544800f, -0.614400f}},
    {{-0.766700f, -0.309417f, -0.373153f,  1.000000f}, {-0.730700f, -0.584500f, -0.352600f}},
    {{-0.789801f,  0.017588f,  0.584145f,  1.000000f}, {-0.810400f,  0.060600f,  0.582700f}},
    {{-0.814531f, -0.161804f,  0.455542f,  1.000000f}, {-0.820700f, -0.378800f,  0.427700f}},
    {{-0.599047f, -0.277577f,  0.649334f,  1.000000f}, {-0.572500f, -0.534200f,  0.622000f}},
    {{-0.668080f, -0.402034f,  0.387223f,  1.000000f}, {-0.601600f, -0.722800f,  0.340100f}},
    {{ 0.189855f,  0.268075f,  0.806957f,  1.000000f}, { 0.055500f,  0.527400f,  0.847800f}},
    {{ 0.346623f,  0.001532f,  0.933423f,  1.000000f}, { 0.360300f,  0.040200f,  0.932000f}},
    {{ 0.382984f, -0.263312f,  0.802304f,  1.000000f}, { 0.367200f, -0.549600f,  0.750400f}},
    {{ 0.095755f, -0.449877f,  0.730060f,  1.000000f}, { 0.100000f, -0.769600f,  0.630600f}},
    {{ 0.810112f,  0.269686f,  0.001912f,  1.000000f}, {-0.547100f,  0.836800f, -0.020800f}},
    {{ 0.979458f,  0.001503f,  0.047190f,  1.000000f}, { 0.999200f,  0.003900f,  0.041000f}},
    {{ 0.809412f, -0.339692f, -0.154807f,  1.000000f}, { 0.767100f, -0.631400f, -0.113900f}},
    {{ 0.469360f, -0.508226f, -0.442249f,  1.000000f}, { 0.393300f, -0.837300f, -0.379800f}},
    {{ 0.299683f, -0.603792f, -0.310957f,  1.000000f}, { 0.200300f, -0.949300f, -0.242500f}},
    {{-0.124433f, -0.508155f, -0.638605f,  1.000000f}, {-0.105300f, -0.845700f, -0.523200f}},
    {{ 0.184378f, -0.654627f, -0.015482f,  1.000000f}, { 0.114900f, -0.993200f, -0.017600f}},
    {{-0.110982f, -0.603585f, -0.413690f,  1.000000f}, {-0.061200f, -0.954500f, -0.291900f}},
    {{-0.294938f, -0.631492f, -0.160506f,  1.000000f}, {-0.211400f, -0.971000f, -0.111700f}},
    {{-0.473571f, -0.512260f, -0.408423f,  1.000000f}, {-0.402700f, -0.842000f, -0.359000f}},
    {{-0.641366f, -0.487405f, -0.146062f,  1.000000f}, {-0.558500f, -0.821200f, -0.117300f}},
    {{-0.223606f, -0.641962f,  0.171214f,  1.000000f}, {-0.152800f, -0.979800f,  0.128800f}},
    {{-0.516000f, -0.556936f,  0.146696f,  1.000000f}, {-0.421200f, -0.898700f,  0.122200f}},
    {{-0.306298f, -0.514104f,  0.556729f,  1.000000f}, {-0.265400f, -0.851800f,  0.451600f}},
    {{ 0.095020f, -0.613930f,  0.394301f,  1.000000f}, { 0.060500f, -0.955300f,  0.289400f}},
    {{ 0.667546f, -0.452814f,  0.258667f,  1.000000f}, { 0.600300f, -0.771500f,  0.210800f}},
    {{ 0.586184f, -0.533585f, -0.050270f,  1.000000f}, { 0.491800f, -0.869100f, -0.052900f}},
    {{ 0.383274f, -0.600305f,  0.191415f,  1.000000f}, { 0.296200f, -0.944000f,  0.145400f}},
    {{ 0.372899f, -0.499471f,  0.529957f,  1.000000f}, { 0.329700f, -0.819800f,  0.468200f}},
    {{ 0.065997f,  0.260735f,  0.827504f,  1.000000f}, { 0.062000f,  0.170300f,  0.983400f}},
    {{-0.056060f,  0.266118f,  0.827534f,  1.000000f}, {-0.051700f,  0.164300f,  0.985100f}},
    {{-0.186281f,  0.274110f,  0.806970f,  1.000000f}, {-0.428900f,  0.350300f,  0.832700f}},
    {{ 0.086699f,  0.382759f,  0.769302f,  1.000000f}, { 0.939000f,  0.269100f, -0.214300f}},
    {{-0.002565f,  0.386216f,  0.797870f,  1.000000f}, {-0.000500f,  0.427800f,  0.903900f}},
    {{-0.069827f,  0.398113f,  0.769187f,  1.000000f}, {-0.973700f,  0.187700f, -0.129200f}},
    {{-0.079321f,  0.600296f,  0.637339f,  1.000000f}, {-0.998300f, -0.036100f,  0.046800f}},
    {{-0.006011f,  0.603230f,  0.661463f,  1.000000f}, { 0.013400f,  0.671800f,  0.740600f}},
    {{-0.082502f,  0.772411f,  0.419514f,  1.000000f}, {-0.668100f,  0.680900f,  0.300000f}},
    {{ 0.087895f,  0.755943f,  0.411653f,  1.000000f}, { 0.991100f,  0.055400f,  0.121500f}},
    {{ 0.088184f,  0.839208f,  0.065193f,  1.000000f}, { 0.650100f,  0.759700f,  0.017000f}},
    {{-0.084080f,  0.838725f,  0.065953f,  1.000000f}, {-0.965700f,  0.182900f, -0.184200f}},
    {{ 0.085181f,  0.789598f, -0.260989f,  1.000000f}, { 0.679600f,  0.708500f, -0.190300f}},
    {{-0.086261f,  0.789828f, -0.257015f,  1.000000f}, {-0.993200f,  0.113900f, -0.025000f}},
    {{-0.084382f,  0.659654f, -0.587534f,  1.000000f}, {-0.955900f,  0.290900f,  0.040700f}},
    {{ 0.086062f,  0.681591f, -0.552273f,  1.000000f}, { 0.653100f,  0.666200f, -0.360100f}},
    {{ 0.020972f,  0.544401f, -0.713857f,  1.000000f}, {-0.031700f,  0.549400f, -0.834900f}},
    {{ 0.086354f,  0.377395f, -0.762975f,  1.000000f}, { 0.946500f,  0.185500f,  0.264100f}},
    {{-0.074598f,  0.392710f, -0.749959f,  1.000000f}, {-0.967700f,  0.135500f,  0.212400f}},
    {{ 0.087116f,  0.588992f,  0.636555f,  1.000000f}, { 0.998100f, -0.012100f, -0.059700f}},
    {{ 0.189855f,  0.268075f,  0.806957f,  1.000000f}, { 0.453300f,  0.347800f,  0.820700f}},
    {{ 0.097463f,  0.540446f, -0.689328f,  1.000000f}, { 0.999300f,  0.032600f,  0.019100f}},
    {{ 0.262611f, -0.618508f, -0.174969f,  1.000000f}, {-0.196300f,  0.975200f,  0.102600f}},
    {{-0.220693f, -0.622175f, -0.168993f,  1.000000f}, { 0.163300f,  0.978600f,  0.125400f}},
    {{-0.122634f, -0.632670f,  0.154836f,  1.000000f}, { 0.079700f,  0.992300f, -0.095300f}},
    {{ 0.614194f, -0.328006f,  0.538955f,  1.000000f}, {-0.594300f,  0.630600f, -0.499100f}},
    {{ 0.626453f, -0.132493f,  0.682943f,  1.000000f}, {-0.646300f,  0.337400f, -0.684400f}},
    {{ 0.831686f, -0.132569f,  0.395524f,  1.000000f}, {-0.831800f,  0.404800f, -0.379800f}},
    {{-0.185758f, -0.327912f,  0.803436f,  1.000000f}, { 0.208300f,  0.626700f, -0.750900f}},
    {{-0.444393f, -0.132542f,  0.817469f,  1.000000f}, { 0.466300f,  0.383300f, -0.797300f}},
    {{-0.004191f, -0.168937f,  0.927587f,  1.000000f}, { 0.006100f,  0.409800f, -0.912200f}},
    {{-0.185760f, -0.327910f, -0.803436f,  1.000000f}, { 0.205300f,  0.625700f,  0.752600f}},
    {{-0.004191f, -0.168938f, -0.927586f,  1.000000f}, { 0.001600f,  0.390600f,  0.920600f}},
    {{-0.444391f, -0.132539f, -0.817471f,  1.000000f}, { 0.466400f,  0.383300f,  0.797300f}},
    {{ 0.614192f, -0.328009f, -0.538954f,  1.000000f}, {-0.595500f,  0.626300f,  0.503100f}},
    {{ 0.831686f, -0.132568f, -0.395523f,  1.000000f}, {-0.848600f,  0.384100f,  0.363900f}},
    {{ 0.643818f, -0.009824f, -0.730910f,  1.000000f}, {-0.689000f,  0.004300f,  0.724800f}},
    {{ 0.858696f,  0.022243f, -0.457268f,  1.000000f}, {-0.894000f, -0.066000f,  0.443300f}},
    {{ 0.900284f,  0.145054f, -0.109079f,  1.000000f}, {-0.876100f, -0.470700f,  0.104700f}},
    {{ 0.776066f,  0.146052f, -0.486020f,  1.000000f}, {-0.697400f, -0.516700f,  0.496700f}},
    {{ 0.474391f,  0.144378f, -0.795390f,  1.000000f}, {-0.460700f, -0.471300f,  0.752100f}},
    {{-0.028955f,  0.068612f, -0.970385f,  1.000000f}, { 0.025300f, -0.230500f,  0.972700f}},
    {{-0.430545f,  0.022237f, -0.883566f,  1.000000f}, { 0.445200f, -0.039100f,  0.894600f}},
    {{-0.448243f,  0.145951f, -0.815375f,  1.000000f}, { 0.462800f, -0.493800f,  0.736200f}},
    {{-0.958746f,  0.022224f, -0.144157f,  1.000000f}, { 0.986000f, -0.070000f,  0.151400f}},
    {{-0.791274f,  0.145015f, -0.450430f,  1.000000f}, { 0.760200f, -0.482500f,  0.435100f}},
    {{-0.908503f,  0.146143f, -0.071077f,  1.000000f}, { 0.864000f, -0.501500f,  0.044000f}},
    {{-0.875970f,  0.143075f,  0.252198f,  1.000000f}, { 0.840600f, -0.480300f, -0.250500f}},
    {{-0.901264f, -0.132539f, -0.177671f,  1.000000f}, { 0.900800f,  0.389800f,  0.191400f}},
    {{-0.875535f, -0.210278f,  0.102171f,  1.000000f}, { 0.877100f,  0.469600f, -0.100700f}},
    {{-0.926703f,  0.010574f,  0.255380f,  1.000000f}, { 0.967400f, -0.016400f, -0.252600f}},
    {{-0.430565f,  0.022216f,  0.883554f,  1.000000f}, { 0.451300f, -0.059200f, -0.890400f}},
    {{-0.665089f,  0.145100f,  0.626962f,  1.000000f}, { 0.652600f, -0.461000f, -0.601300f}},
    {{-0.345741f,  0.147344f,  0.857347f,  1.000000f}, { 0.288300f, -0.505300f, -0.813300f}},
    {{-0.184303f,  0.257070f,  0.796695f,  1.000000f}, { 0.775000f,  0.026100f, -0.631400f}},
    {{ 0.075344f,  0.139314f,  0.930031f,  1.000000f}, {-0.084700f, -0.504700f, -0.859100f}},
    {{-0.003099f,  0.244539f,  0.823377f,  1.000000f}, { 0.004000f, -0.537100f, -0.843500f}},
    {{-0.009268f,  0.020817f,  0.973197f,  1.000000f}, { 0.054600f, -0.081600f, -0.995200f}},
    {{ 0.583599f,  0.067783f,  0.768164f,  1.000000f}, {-0.600400f, -0.226200f, -0.767000f}},
    {{ 0.858694f,  0.022241f,  0.457270f,  1.000000f}, {-0.883200f, -0.052200f, -0.466100f}},
    {{ 0.833428f,  0.146160f,  0.391659f,  1.000000f}, {-0.795500f, -0.499400f, -0.343300f}},
    {{ 0.339367f,  0.002159f, -0.914479f,  1.000000f}, {-0.327600f, -0.032600f,  0.944200f}},
    {{ 0.375743f, -0.252537f, -0.786977f,  1.000000f}, {-0.372700f,  0.551900f,  0.746000f}},
    {{ 0.094085f, -0.434231f, -0.717214f,  1.000000f}, {-0.105800f,  0.772900f,  0.625600f}},
    {{-0.802712f,  0.002163f, -0.536885f,  1.000000f}, { 0.821200f, -0.015100f,  0.570400f}},
    {{-0.586781f, -0.267659f, -0.636445f,  1.000000f}, { 0.574900f,  0.547300f,  0.608300f}},
    {{-0.758462f, -0.252598f, -0.411955f,  1.000000f}, { 0.750600f,  0.532600f,  0.391000f}},
    {{-0.778853f, -0.350305f, -0.117527f,  1.000000f}, { 0.745000f,  0.661200f,  0.088600f}},
    {{-0.773897f,  0.016132f,  0.572375f,  1.000000f}, { 0.805200f, -0.063200f, -0.589600f}},
    {{-0.797794f, -0.155781f,  0.446141f,  1.000000f}, { 0.814200f,  0.384500f, -0.435100f}},
    {{-0.586781f, -0.267658f,  0.636446f,  1.000000f}, { 0.564100f,  0.550200f, -0.615700f}},
    {{-0.737942f, -0.339002f,  0.316936f,  1.000000f}, { 0.702200f,  0.655800f, -0.277300f}},
    {{ 0.187850f,  0.251154f,  0.796493f,  1.000000f}, {-0.793900f,  0.017000f, -0.607800f}},
    {{ 0.339393f,  0.002148f,  0.914465f,  1.000000f}, {-0.360800f, -0.047900f, -0.931400f}},
    {{ 0.375743f, -0.252537f,  0.786977f,  1.000000f}, {-0.378700f,  0.533200f, -0.756400f}},
    {{ 0.184750f, -0.380568f,  0.750290f,  1.000000f}, {-0.178300f,  0.730600f, -0.659100f}},
    {{ 0.956707f,  0.016134f,  0.000001f,  1.000000f}, {-0.997600f, -0.068900f, -0.003600f}},
    {{ 0.903069f, -0.155855f,  0.116502f,  1.000000f}, {-0.919400f,  0.373500f, -0.123400f}},
    {{ 0.842832f, -0.269205f, -0.156358f,  1.000000f}, {-0.817100f,  0.552600f,  0.163900f}},
    {{ 0.774599f, -0.338138f,  0.187695f,  1.000000f}, {-0.725100f,  0.663500f, -0.184500f}},
    {{ 0.461364f, -0.491216f, -0.434889f,  1.000000f}, {-0.409000f,  0.833600f,  0.371200f}},
    {{ 0.093701f, -0.594685f, -0.388546f,  1.000000f}, {-0.055700f,  0.950500f,  0.305800f}},
    {{-0.301434f, -0.496864f, -0.547394f,  1.000000f}, { 0.270000f,  0.850300f,  0.451800f}},
    {{-0.600405f, -0.487432f, -0.221975f,  1.000000f}, { 0.509100f,  0.835900f,  0.205200f}},
    {{-0.519514f, -0.544810f,  0.147404f,  1.000000f}, { 0.431300f,  0.895600f, -0.109400f}},
    {{-0.465692f, -0.495091f,  0.401699f,  1.000000f}, { 0.390100f,  0.842300f, -0.372100f}},
    {{-0.109309f, -0.584524f,  0.407533f,  1.000000f}, { 0.069300f,  0.950300f, -0.303500f}},
    {{-0.122218f, -0.491149f,  0.627860f,  1.000000f}, { 0.103600f,  0.846700f, -0.521900f}},
    {{ 0.598497f, -0.506614f, -0.000004f,  1.000000f}, {-0.517100f,  0.855900f,  0.011200f}},
    {{ 0.461365f, -0.491216f,  0.434888f,  1.000000f}, {-0.386000f,  0.842500f, -0.375700f}},
    {{ 0.285302f, -0.596028f,  0.271148f,  1.000000f}, {-0.200300f,  0.957600f, -0.207300f}},
    {{-0.184995f,  0.256560f,  0.797469f,  1.000000f}, { 0.756700f,  0.615000f, -0.221800f}},
    {{-0.080501f,  0.756811f,  0.410386f,  1.000000f}, {-0.712700f, -0.647700f, -0.269400f}},
    {{ 0.089305f,  0.821747f,  0.064175f,  1.000000f}, { 0.745000f, -0.666600f, -0.024700f}},
    {{ 0.085061f,  0.772866f, -0.255369f,  1.000000f}, { 0.692500f, -0.698100f,  0.181900f}},
    {{ 0.086248f,  0.667162f, -0.541049f,  1.000000f}, { 0.713900f, -0.604200f,  0.353900f}},
    {{ 0.188489f,  0.250543f,  0.797436f,  1.000000f}, {-0.697400f,  0.670100f, -0.254100f}}
};
static const int basketNumVertices = 182;

static const GLint basketIndices[] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 
    16, 17, 17, 16, 18, 16, 19, 18, 15, 20, 16, 16, 20, 19, 14, 13, 
    15, 13, 21, 15, 15, 21, 20, 11, 22, 23, 23, 24, 25, 22, 26, 23, 
    23, 26, 24, 26, 27, 24, 11, 10, 22, 28, 29, 30, 31, 32, 28, 0, 
    33, 31, 28, 32, 29, 31, 33, 32, 32, 34, 29, 33, 35, 32, 32, 35, 
    34, 0, 2, 33, 36, 37, 38, 39, 40, 36, 36, 40, 37, 40, 41, 37, 
    39, 42, 40, 40, 42, 41, 42, 43, 41, 8, 7, 39, 7, 44, 39, 39, 
    44, 42, 42, 45, 43, 5, 46, 47, 46, 48, 47, 47, 48, 49, 48, 50, 
    49, 5, 4, 46, 19, 20, 51, 20, 23, 51, 51, 23, 25, 21, 52, 20, 
    20, 52, 23, 13, 52, 21, 52, 11, 23, 13, 53, 52, 53, 11, 52, 13, 
    12, 53, 53, 54, 11, 54, 9, 11, 27, 26, 30, 26, 28, 30, 22, 55, 
    26, 26, 55, 28, 55, 31, 28, 10, 56, 22, 22, 56, 55, 55, 0, 31, 
    56, 57, 55, 55, 57, 0, 9, 56, 10, 34, 35, 38, 35, 36, 38, 33, 
    58, 35, 35, 58, 36, 58, 39, 36, 2, 59, 33, 33, 59, 58, 59, 60, 
    58, 58, 60, 39, 60, 8, 39, 2, 1, 59, 1, 61, 59, 59, 61, 60, 
    60, 6, 8, 45, 42, 62, 62, 42, 49, 42, 47, 49, 44, 63, 42, 42, 
    63, 47, 44, 7, 63, 63, 5, 47, 7, 64, 63, 63, 64, 5, 6, 65, 
    7, 65, 64, 7, 64, 3, 5, 50, 48, 66, 48, 17, 66, 66, 17, 18, 
    46, 67, 48, 48, 67, 17, 67, 15, 17, 4, 67, 46, 67, 14, 15, 4, 
    14, 67, 4, 68, 14, 68, 12, 14, 69, 54, 12, 12, 54, 53, 70, 71, 
    69, 69, 71, 54, 71, 9, 54, 72, 73, 70, 70, 73, 71, 72, 74, 73, 
    71, 56, 9, 71, 75, 56, 73, 75, 71, 75, 57, 56, 73, 74, 75, 75, 
    76, 57, 74, 76, 75, 76, 0, 57, 72, 77, 74, 74, 78, 76, 76, 1, 
    0, 76, 78, 1, 78, 61, 1, 74, 77, 78, 77, 79, 78, 78, 79, 61, 
    61, 79, 60, 79, 6, 60, 77, 80, 79, 4, 81, 68, 68, 69, 12, 68, 
    82, 69, 81, 82, 68, 82, 70, 69, 82, 72, 70, 4, 3, 81, 81, 83, 
    82, 82, 83, 72, 79, 65, 6, 79, 80, 65, 80, 84, 65, 84, 3, 65, 
    65, 3, 64, 77, 72, 80, 72, 83, 80, 80, 83, 84, 83, 81, 84, 84, 
    81, 3, 62, 85, 45, 45, 86, 43, 43, 87, 41, 85, 88, 89, 86, 90, 
    87, 90, 89, 91, 91, 92, 93, 94, 95, 93, 93, 95, 96, 96, 97, 98, 
    97, 99, 98, 100, 101, 99, 101, 102, 25, 101, 103, 99, 25, 102, 51, 104, 
    92, 89, 94, 93, 92, 62, 105, 85, 45, 85, 86, 43, 86, 87, 85, 105, 
    88, 86, 85, 89, 86, 89, 90, 88, 104, 89, 104, 94, 92, 96, 95, 97, 
    97, 100, 99, 100, 106, 101, 101, 106, 102, 101, 25, 103, 25, 24, 103, 91, 
    89, 92, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 
    121, 122, 123, 124, 123, 18, 124, 122, 124, 125, 124, 18, 125, 125, 18, 19, 
    120, 122, 121, 122, 125, 121, 117, 126, 127, 126, 51, 24, 127, 126, 128, 126, 
    24, 128, 128, 24, 27, 117, 127, 118, 129, 130, 131, 130, 30, 131, 131, 30, 
    29, 129, 131, 132, 131, 29, 132, 132, 29, 34, 133, 129, 134, 134, 129, 135, 
    129, 132, 135, 136, 137, 138, 137, 37, 138, 138, 37, 139, 136, 138, 140, 138, 
    139, 140, 140, 139, 141, 114, 136, 115, 115, 136, 142, 136, 140, 142, 111, 143, 
    144, 143, 49, 50, 144, 143, 145, 143, 50, 145, 111, 144, 112, 19, 51, 125, 
    125, 51, 126, 121, 125, 146, 125, 126, 146, 146, 126, 117, 121, 146, 147, 147, 
    146, 117, 121, 147, 119, 147, 117, 148, 148, 117, 116, 27, 30, 128, 128, 30, 
    130, 127, 128, 149, 128, 130, 149, 149, 130, 129, 118, 127, 150, 127, 149, 150, 
    149, 129, 133, 150, 149, 151, 149, 133, 151, 116, 118, 150, 151, 133, 152, 152, 
    133, 134, 34, 38, 132, 132, 38, 137, 38, 37, 137, 135, 132, 153, 132, 137, 
    153, 153, 137, 136, 135, 153, 154, 154, 153, 155, 153, 136, 155, 155, 136, 114, 
    134, 135, 154, 134, 154, 156, 154, 155, 156, 155, 114, 113, 141, 157, 140, 157, 
    49, 140, 140, 49, 143, 142, 140, 158, 140, 143, 158, 142, 158, 115, 158, 143, 
    111, 115, 158, 159, 158, 111, 159, 113, 115, 160, 160, 115, 159, 159, 111, 110, 
    50, 66, 145, 145, 66, 123, 66, 18, 123, 144, 145, 161, 145, 123, 161, 161, 
    123, 122, 112, 144, 162, 144, 161, 162, 162, 161, 163, 161, 122, 163, 163, 122, 
    120, 110, 112, 164, 112, 162, 164, 164, 162, 163, 163, 120, 119, 165, 119, 148, 
    119, 147, 148, 107, 165, 166, 166, 165, 148, 107, 166, 108, 166, 148, 167, 148, 
    116, 167, 167, 116, 150, 167, 150, 168, 150, 151, 168, 166, 167, 108, 108, 167, 
    168, 168, 151, 152, 109, 108, 169, 108, 168, 169, 168, 152, 169, 152, 134, 156, 
    152, 156, 169, 169, 156, 170, 170, 156, 155, 109, 169, 171, 169, 170, 171, 171, 
    170, 172, 170, 155, 172, 172, 155, 113, 163, 119, 165, 163, 165, 173, 164, 163, 
    173, 173, 165, 107, 110, 164, 174, 164, 173, 174, 174, 173, 175, 173, 107, 175, 
    175, 107, 109, 172, 113, 160, 171, 172, 175, 175, 172, 174, 172, 160, 174, 174, 
    160, 110, 160, 159, 110, 109, 171, 175, 141, 139, 176, 141, 90, 88, 141, 176, 
    90, 94, 177, 178, 177, 96, 178, 96, 98, 179, 179, 98, 99, 180, 99, 106, 
    106, 103, 102, 106, 99, 103, 104, 90, 91, 94, 91, 177, 157, 141, 181, 141, 
    88, 181, 88, 90, 104, 104, 91, 94, 96, 179, 178, 179, 99, 180, 51, 102, 
    103, 51, 103, 24, 62, 49, 157, 62, 181, 105, 87, 139, 41, 87, 90, 176, 
    94, 178, 95, 93, 96, 177, 97, 178, 179, 97, 180, 100, 41, 139, 37, 62, 
    157, 181, 87, 176, 139, 105, 181, 88, 93, 177, 91, 97, 95, 178, 97, 179, 
    180, 100, 180, 106 
};
static const int basksetNumIndices = 1092;

class Basket : public Entity {
public:
    Basket(byte materialId) {
        if(m_basketMeshId == 0xFF) {
            Mesh *basketMesh = new Mesh(std::vector<Vertex>(basketVertices, basketVertices + basketNumVertices), std::vector<GLint>(basketIndices, basketIndices + basksetNumIndices));
            m_basketMeshId = basketMesh->getId();

            MeshRegistry *registry = MeshRegistry::getRegistry();
            registry->registerMesh(basketMesh);
        }

        p_meshId = m_basketMeshId;
        p_materialId = materialId;
    }

    ~Basket() {}

private:
    static byte m_basketMeshId;
};

// Initalize to sentinal 255 as it's greater than the max number of meshes (128)
byte Basket::m_basketMeshId = 0xFF;

#endif