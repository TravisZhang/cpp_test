#include <bits/stdc++.h>

using namespace std;

// typedef double(*Activefun_def)(double sum); 

// double sigmoid(double sum)
// {
//     return 1 / (1 + exp(-sum));
// }

template<class T>
class Myneuron
{
public:
    Myneuron()
    {

    }
    ~Myneuron()
    {
        if(weight_ != NULL)
            delete [] weight_;
        weight_ = NULL;
    }

    // void set_input_num(auto in)
    // {
    //     in = in < 0 ? 0 : in;
    //     size_t n = static_cast<size_t>(in);
    //     input_num_ = n;
    // }

    void init(T* input_data, size_t input_num);

    void set_input_data(T* in) { input_data_ = in; };

    void set_output(T* out) { output_ = out; }

    void set_current_delta(T d) { current_delta_ = d; }

    void set_current_delta_h(T d) { current_delta_ = output_[0] * (1-output_[0]) * d; }

    auto get_current_delta() const { return current_delta_; }

    auto get_weight(size_t i) const { return weight_[i]; }

    void update_weight(T rate);

    void update_bias(T rate) { bias_ -= rate * current_delta_; }

    void simple_sum();

    void sigmoid() { *output_ = 1 / (1 + exp(-h_)); }

private:
    size_t input_num_;
    T* input_data_;
    T* weight_;
    T bias_;
    T* output_;
    T h_; // output from hidden layer before activation fun
    T current_delta_;
    T last_delta;
    // Activefun_def af_;
    
};

template<class T>
void Myneuron<T>::init(T* input_data, size_t input_num)
{
    input_data_ = input_data;
    input_num_ = input_num;
    bias_ = (rand() % 100000)*0.00001;
    weight_ = new (std::nothrow) T[input_num]; 

    for(size_t i = 0; i < input_num; ++i)
    {
        weight_[i] = (rand() % 100000)*0.00001;
    }
}

template<class T>
void Myneuron<T>::simple_sum()
{
    h_ = 0;
    for(size_t i = 0; i < input_num_; ++i)
    {
        h_ += input_data_[i] * weight_[i];
    }
    h_ += bias_;
}

template<class T>
void Myneuron<T>::update_weight(T rate)
{
    for(size_t i = 0; i < input_num_; ++i)
    {
        weight_[i] -= rate * current_delta_ * input_data_[i];
    }
}



/********************************************************************/

template<class T>
class Mylayer
{
public:
    Mylayer()
    {

    }
    ~Mylayer()
    {
        if(input_data_ != NULL)
            delete [] input_data_;
        input_data_ = NULL;
    }

    // void set_input_num(auto in)
    // {
    //     in = in < 0 ? 0 : in;
    //     size_t n = static_cast<size_t>(in);
    //     input_num_ = n;
    // }

    auto get_input_data() const { return input_data_; }
    auto get_neuron_num() const { return neuron_num_; }
    auto get_hidden_sum() const { return neuron_delta_sum_; }

    void init(size_t input_num, size_t neuron_num);

    // void compute_output_delta();
    void compute_hidden_sum(size_t neuron_index);

    vector<Myneuron<T>> neuron;


private:
    size_t input_num_;
    size_t neuron_num_;
    T *input_data_;
    T neuron_delta_sum_;
    
};

template<class T>
void Mylayer<T>::init(size_t input_num, size_t neuron_num)
{
    input_num_ = input_num;
    neuron_num_ = neuron_num;
    input_data_ = new (std::nothrow) T[input_num];

    cout << "[layer] input_num: " << input_num_ << " neuron_num: " << neuron_num_ << endl;

    neuron.clear();
    neuron.resize(neuron_num);
    for(size_t i = 0; i < neuron_num; ++i)
    {
        neuron[i].init(input_data_, input_num);
    }

}

template<class T>
void Mylayer<T>::compute_hidden_sum(size_t neuron_index)
{
    neuron_delta_sum_ = 0;
    for(size_t i = 0; i < neuron_num_; ++i)
    {
        neuron_delta_sum_ += neuron[i].get_current_delta() * neuron[i].get_weight(neuron_index);
    }
}

/********************************************************************/


template<class T>
class Mydnn
{
public:
    Mydnn()
    {

    }
    ~Mydnn()
    {
        if(output_data_ != NULL)
            delete [] output_data_;
        output_data_ = NULL;
    }

    // void set_input_num(auto in)
    // {
    //     in = in < 0 ? 0 : in;
    //     size_t n = static_cast<size_t>(in);
    //     input_num_ = n;
    // }

    // void set_output_num(auto in)
    // {
    //     in = in < 0 ? 0 : in;
    //     size_t n = static_cast<size_t>(in);
    //     output_num_ = n;
    // }

    void set_layer_num(vector<size_t>& in)
    {
        layer_neuron_num_.resize(in.size());
        for(size_t i = 0; i < in.size(); ++i)
        {
            layer_neuron_num_[i] = in[i] < 1 ? 1 : in[i];
        }
    }


    auto input_num() const { return input_num_; }
    auto output_num() const { return output_num_; }
    auto layer_num() const { return layer_num_; }

    void init();

    void compute_output(vector<T>& in);

    void train();

    void print_output()
    {
        cout << "print output" << endl;
        for(size_t i = 0; i < output_num_; ++i)
        {
            cout<< "output_data[" << i << "]: " << output_data_[i] << endl;
        }
        cout << "print output finished" << endl;
    }

    vector<Mylayer<T>> layer;

    vector<vector<T>> sample_data;

    vector<T> labels;

private:
    size_t input_num_;
    size_t output_num_;
    size_t layer_num_;
    size_t hidden_num_;
    vector<size_t> layer_neuron_num_;
    T *input_data_;
    T *output_data_;
    
    
};

template<class T>
void Mydnn<T>::init()
{
    cout << "dnn init begin" << endl;

    // set layer vector size
    layer_num_ = layer_neuron_num_.size();
    hidden_num_ = layer_num_-2;
    cout << "layer_num: " << layer_num_ << " hidden_num: " << hidden_num_ << endl; 

    // network structure: input_layer*1, hidden_layer*n, output_layer*1, total_num = n+2 (>= 2)
    layer.clear();
    layer.resize(layer_num_);
    for(size_t i = 0; i < layer_num_-1; ++i)
    {
        cout << "init layer[" << i << "]" << endl;
        layer[i].init(layer_neuron_num_[i], layer_neuron_num_[i+1]);
    }

    // connect hidden layers
    input_num_ = layer_neuron_num_[0];
    input_data_ = layer[0].get_input_data(); // set dnn's input the same as layer 0's input(hidden layer 0)
    for(size_t i = 0; i < hidden_num_; ++i)
    {
        for(size_t j = 0; j < layer[i+1].get_neuron_num(); ++j)
        {
            for(size_t k = 0; k < layer[i].get_neuron_num(); ++k)
            {
                T* p_in = layer[i+1].get_input_data();
                layer[i].neuron[k].set_output(&p_in[k]);
            }
        }
    }

    // init output layer
    output_num_ = layer[hidden_num_].get_neuron_num();
    output_data_ = new (std::nothrow) T[output_num_];

    for(size_t i = 0; i < layer[hidden_num_].get_neuron_num(); ++i)
    {
        layer[hidden_num_].neuron[i].set_output(&output_data_[i]);
    }

    cout << "dnn init finished" << endl;

}

template<class T>
void Mydnn<T>::compute_output(vector<T>& in)
{
    T* input_temp = &in[0];
    for(size_t i = 0; i < layer_num_-1; ++i)
    {
        for(size_t j = 0; j < layer[i].get_neuron_num(); ++j)
        {
            if(i == 0)
            {
                layer[i].neuron[j].set_input_data(input_temp);
                layer[i].neuron[j].simple_sum();
                layer[i].neuron[j].sigmoid();
            }
            else
            {
                layer[i].neuron[j].simple_sum();
                layer[i].neuron[j].sigmoid();
            }
        }
    }
}

template<class T>
void Mydnn<T>::train()
{
    cout << "train begin" << endl;

    T rate = 0.2;
    size_t train_num = 10;
    size_t sample_num = sample_data.size();

    for(size_t t = 0; t < train_num; ++t)
    {
        for(size_t s = 0; s < sample_num; ++s)
        {
            cout << "train index: " << t << " sample index: " << s << endl;
            cout << "compute output" << endl;
            compute_output(sample_data[s]);
            cout << "compute output finished" << endl;

            print_output();

            size_t i = hidden_num_;
            while(1)
            {
                cout << "layer num: " << i << endl;
                for(size_t j = 0; j < layer[i].get_neuron_num(); ++j)
                {
                    if(i == hidden_num_) // output layer
                    {
                        // cout << "layer num: " << i << endl;

                        T o_d = -output_data_[j] * (1-output_data_[j]) * (labels[s]-output_data_[j]);
                        layer[i].neuron[j].set_current_delta(o_d);
                        layer[i].neuron[j].update_weight(rate);
                        layer[i].neuron[j].update_bias(rate);
                    }
                    else // hidden layer
                    {
                        // cout << "layer num: " << i << endl;

                        layer[i+1].compute_hidden_sum(j);
                        T h_d = layer[i+1].get_hidden_sum();

                        layer[i].neuron[j].set_current_delta_h(h_d);
                        layer[i].neuron[j].update_weight(rate);
                        layer[i].neuron[j].update_bias(rate);
                    }
                }
                if(i-- == 0)
                    break;
            }
        }
    }

    cout << "train finished" << endl;

}

/********************************************************************/


int main()
{
    vector<vector<double>> data = {{0,0},{0,1},{1,0},{1,1}};
    vector<double> labels = {0,1,1,0};
    vector<size_t> layer_neuron_num = {2,3,1};

    cout << "params init finished" << endl;

    Mydnn<double> mydnn;
    mydnn.sample_data = data;
    mydnn.labels = labels;
    mydnn.set_layer_num(layer_neuron_num);

    cout << "dnn params set" << endl;

    mydnn.init();

    mydnn.train();

   return 0;
}